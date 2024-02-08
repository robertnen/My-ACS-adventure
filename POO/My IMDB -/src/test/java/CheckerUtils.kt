import com.fasterxml.jackson.databind.JsonNode
import com.fasterxml.jackson.databind.ObjectMapper
import com.fasterxml.jackson.databind.node.ArrayNode
import com.fasterxml.jackson.databind.node.ObjectNode
import org.example.*
import org.example.Observer
/*
 *   FIXME: Pentru a functiona checker-ul aceste clase trebuie sa existe si sa aiba functiile si membrii necesari
 */

import org.reflections.Reflections
import java.io.File
import java.io.IOException
import java.lang.reflect.Constructor
import java.lang.reflect.Field
import java.lang.reflect.Method
import java.lang.reflect.Modifier
import java.lang.reflect.ParameterizedType
import java.nio.file.Files
import java.util.*
import java.util.function.Consumer
import kotlin.collections.ArrayList
import java.util.TreeSet
import javax.lang.model.type.PrimitiveType

class CheckerUtils {
    companion object {
        private var mapper: ObjectMapper = ObjectMapper()
        private var types = arrayOf(
            java.lang.String::class.java,
            java.lang.Short::class.java,
            java.lang.Integer::class.java,
            java.lang.Double::class.java,
            java.lang.Float::class.java,
            java.lang.Long::class.java,
            java.lang.Boolean::class.java,
            java.lang.Character::class.java,
            java.util.Date::class.java,
        )

        fun checkSingleton(type: Class<*>, maxScore: Float): Float {
            var score = maxScore
            val scale = maxScore / 5
            val fields = type.declaredFields

            // fields 1.0f
            var correctFields = 0
            for (field in fields)
                if (Modifier.isPrivate(field.modifiers) || Modifier.isStatic(field.modifiers))
                    correctFields++
            if (correctFields != fields.size) {
                println("Singleton ${type.simpleName} has $correctFields/${fields.size} fields that respect the requirements")
                score -= (1.0f - (correctFields.toFloat() / fields.size.toFloat())) * scale
            }

            // constructors 1.0f
            if (!type.declaredConstructors.all { constructor -> Modifier.isPrivate(constructor.modifiers) }) {
                println("Singleton ${type.simpleName} can be instantiated from outside the class")
                score -= scale
            }

            // instance 1.0f
            if (fields.none { field -> Modifier.isStatic(field.modifiers) && Modifier.isPrivate(field.modifiers) && field.type == type }) {
                println("Singleton ${type.simpleName} does not have an instance field or it does not have the correct modifiers")
                score -= scale
                return score
            }

            // getInstance 2.0f
            val getInstance : Method? = type.methods.find { method -> method.name.equals("getInstance") }
            val instance : Field = type.declaredFields.find { field -> field.name.equals("instance") }!!
            instance.isAccessible = true

            val inst = getInstance?.invoke(null)
            if (instance.get(null) !== inst) {
                println("Singleton ${type.simpleName} does not work correctly")
                score -= 2.0f * scale
            }
            return score
        }

        fun checkBuilder(type: Class<*>, maxScore: Float, builtType: Class<*>? = null): Float {
            var result = 0.0f

            val fields = type.declaredFields
            val methods = type.declaredMethods

            var correctFields = 0
            var totalFields = 0

            val setterMethods = ArrayList<Method>()

            // field setters
            for (method in methods) {
                for (field in fields) {
                    if (method.name == field.name) {
                        totalFields++
                        if (method.returnType != type) continue
                        setterMethods.add(method)
                        correctFields++
                    }
                }
            }


            result += correctFields.toFloat() / totalFields.toFloat() * .5f

            val constructor = type.declaredConstructors[0]
            val cut:List<Any?> = constructor.parameters.map{ getRandomValue(it.type) }
            val par = Array(cut.size){
                cut[it]
            }

            val instance = constructor.newInstance(*par)
            result += .1f

            // build method
            if (builtType != null) {
                correctFields = 0
                totalFields = 0
                val build = methods.find { it.name == "build" && it.returnType == builtType }
                if (build != null) {
                    for (method in setterMethods) {
                        method.invoke(instance, getRandomValue(method.parameterTypes[0]))
                    }
                    val built = build.invoke(instance)
                    val builtFields = builtType.declaredFields
                    for (builtField in builtFields) {
                        val builderField = fields.find { it.name == builtField.name } ?: continue
                        totalFields++
                        builtField.isAccessible = true
                        builderField.isAccessible = true
                        if(builtField.get(built) === builderField.get(instance)) {
                            correctFields++
                        }
                    }
                }
                result += correctFields.toFloat() / totalFields.toFloat() * .4f
            } else {
                println("You have implemented a setter builder so your score is capped at 6.\n" +
                        "You can implement the classic pattern for the remaining 4 points")
            }

            return result * maxScore
        }

        private fun getRandomValue(clazz: Class<*>?): Any? {
            if (clazz?.isPrimitive == true) {
                return when (clazz.name) {
                    "int" -> 22
                    "long" -> 0
                    "boolean" -> false
                    "char" -> 'a'
                    "float" -> 1.1
                    else -> Any()
                }
            }
            return when(clazz) {
                Integer::class.java -> Random().nextInt()
                String::class.java -> "Random string"
                Double::class.java -> Random().nextDouble()
                Float::class.java -> Random().nextFloat()
                Long::class.java -> Random().nextLong()
                Short::class.java -> Random().nextInt().toShort()
                Boolean::class.java -> Random().nextBoolean()
                AccountType::class.java -> AccountType.entries[Random().nextInt(0, AccountType.entries.size)]
                else -> clazz?.declaredConstructors?.find { it.parameterCount == 0 }?.newInstance()
            }
        }

        fun checkFactory(type: Class<*>, enum: Class<*>, maxScore: Float): Float {
            var score = 0.0f

            val subclasses = enum.enumConstants.map { Class.forName(type.packageName + "."+ it) }
            var returnType = subclasses[0]
            while (returnType.superclass.packageName == type.packageName) {
                returnType = returnType.superclass
            }
            if (!subclasses.all { returnType.isAssignableFrom(it) }) {
                println("The return type is wrong or you have enum constants that do not extend the same class")
                return score
            }

            val methods = type.declaredMethods
            if (methods.size == 1) {
                val method = methods[0]

                val pars = returnType.declaredConstructors[0].parameters.map { getRandomValue(it.type) }
                var parArr = Array(pars.size) { pars[it] }


                if (method.returnType == returnType && method.parameterCount == pars.size && method.parameterTypes[pars.size - 1] == enum) {
                    score += .1f;
                }

                for (enumConstant in enum.enumConstants) {
                    val enumValue = enum.getField(enumConstant.toString()).get(null)
                    val factory = type.getDeclaredConstructor().newInstance()
                    val result = method.invoke(factory, *parArr)
                    if (result == null) {
                        println("The factory ${type.simpleName} does not return a value for $enumConstant")
                        continue
                    }
                    if (result.javaClass == subclasses.find { it.simpleName == enumConstant.toString() }) {
                        score += .9f / enum.enumConstants.size
                    }
                }
            }

            return score * maxScore
        }

        fun checkStrategy(type: Class<*>, maxScore: Float): Float {
            var score = 0.0f

            val methods = type.declaredMethods
            if (methods.size == 1) {
                val method = methods[0]
                if ((method.returnType == Integer::class.java || method.returnType.name == "int") && method.parameterCount == 0 && method.name == "calculateExperience") {
                    score += .1f;
                }

                val reflections = Reflections(type.packageName)
                val strategies = reflections.getSubTypesOf(type)

                if (strategies.size < 2) {
                    println("Not enough strategies implemented")
                    return score
                }

                for (strategy in strategies) {
                    val constructor = strategy.getDeclaredConstructor()
                    constructor.isAccessible = true
                    val instance = constructor.newInstance()
                    method.invoke(instance) ?: { score -= .9f / strategies.size }
                    score += .9f / strategies.size
                }
                return score * maxScore
            }

            return score * maxScore
        }

        fun checkObserver(type: Class<*>, maxScore: Float): Float {
            var score = 1.0f

            val updateMethod = type.declaredMethods.find { it.name == "update" } ?: return 0.0f

            if (updateMethod.parameterCount != 1 || updateMethod.parameterTypes[0] != String::class.java) {
                println("The update method should have one parameter of type String")
                return 0.0f
            }

            val notificationsField = type.declaredFields.find { it.type.isAssignableFrom(Collection::class.java) && it.type.genericSuperclass == String::class.java } ?: {
                println("You have no collection for incoming notifications")
                score -= .5f
            }

            if (notificationsField.javaClass.isAssignableFrom(Collection::class.java)) {
                println("The notifications field should be a collection")
                score -= .5f
            }

            return score * maxScore
        }

        fun checkSubject(type: Class<*>, maxScore: Float) : Float {
            val subscribe = type.declaredMethods.find { it.name == "subscribe" || it.name == "addObserver" } ?: {
                println("You have no subscribe method")
            }

            val unsubscribe = type.declaredMethods.find { it.name == "unsubscribe" || it.name == "removeObserver" } ?: {
                println("You have no unsubscribe method")
            }

            val notify = type.declaredMethods.find { it.name == "notifyObservers" } ?: {
                println("You have no notifyObservers method")
            }

            val observers = type.declaredFields.find { it.type.isAssignableFrom(Collection::class.java) && it.type.genericSuperclass == Observer::class.java } ?: {
                println("You have no collection for observers")
            }

            if (subscribe == Unit || unsubscribe == Unit || notify == Unit || observers == Unit) {
                return 0.0f
            }

            return maxScore
        }

        private fun getAllFields(type: Class<*>): List<Field> {
            val fields = ArrayList<Field>()
            fields.addAll(type.declaredFields)
            if (type.superclass != null) fields.addAll(getAllFields(type.superclass))
            return fields
        }

        private fun containsAll(type: Class<*>, firstCollection: Collection<*>?, secondCollection: Collection<*>?): Boolean {
            if (firstCollection == null || secondCollection == null) return false
            for (first in firstCollection) {
                var contains = false
                for (second in secondCollection) {
                    if (checkEquals(type, first, second)) contains = true
                }
                if (!contains) return false
            }
            return true
        }

        fun checkEquals(classType: Class<*>, first: Any?, second: Any?): Boolean {
            if (first == null && second == null) return true
            if (first == null || second == null) return false
            if (classType.isPrimitive || classType.isEnum || types.contains(classType))
                return first == second
            val fields = getAllFields(classType)
            return fields.filter { field -> !Modifier.isStatic(field.modifiers) }.
            all { field ->
                field.isAccessible = true
                if (Collection::class.java.isAssignableFrom(field.type)) {
                    val firstCollection = field.get(first) as Collection<*>?
                    val secondCollection = field.get(second) as Collection<*>?
                    if (firstCollection == null && secondCollection == null) return true
                    if (firstCollection == null || secondCollection == null) return false
                    val genericType = (field.genericType as ParameterizedType).actualTypeArguments[0]
                    if (genericType is Class<*>) {
                        return@all containsAll(genericType, firstCollection, secondCollection)
                    }
                    return@all firstCollection == secondCollection
                } else {
                    checkEquals(field.type, field.get(first), field.get(second))
                }
            }
        }

        fun loadUsers() : MutableList<User<*>> {
            val file = File("src/test/resources/testResources/accounts.json")
            val parser = mapper.createParser(Files.readAllBytes(file.toPath()))
            val accounts = mapper.readTree<ArrayNode>(parser)
            val users: MutableList<User<*>> = java.util.ArrayList()
            accounts.forEach(Consumer { account: JsonNode ->
                val accountNode = account as ObjectNode
                val favorites: SortedSet<Comparable<Any>> = TreeSet()
                val contributions: SortedSet<Comparable<Any>> = TreeSet()
                if (accountNode.has("favoriteMovies")) {
                    favorites.addAll(
                        IMDB.getInstance().productions
                            .stream()
                            .filter { production: Production ->
                                accountNode["favoriteMovies"].toString().contains(production.title)
                            }
                            .toList()
                    )
                    accountNode.remove("favoriteMovies")
                }
                if (accountNode.has("favoriteActors")) {
                    favorites.addAll(
                        IMDB.getInstance().actors
                            .stream()
                            .filter { actor: Actor ->
                                accountNode["favoriteActors"].toString().contains(actor.name)
                            }
                            .toList()
                    )
                    accountNode.remove("favoriteActors")
                }
                if (accountNode.has("moviesContribution")) {
                    contributions.addAll(
                        IMDB.getInstance().productions
                            .stream()
                            .filter { production: Production ->
                                accountNode["moviesContribution"].toString().contains(production.title)
                            }
                            .toList()
                    )
                    accountNode.remove("moviesContribution")
                }
                if (accountNode.has("actorsContribution")) {
                    contributions.addAll(
                        IMDB.getInstance().actors
                            .stream()
                            .filter { actor: Actor ->
                                accountNode["actorsContribution"].toString().contains(actor.name)
                            }
                            .toList()
                    )
                    accountNode.remove("actorsContribution")
                }
                try {
                    when (AccountType.valueOf(account["userType"].asText())) {
                        AccountType.Regular -> {
                            val r = mapper.readValue(
                                accountNode.toString(),
                                Regular::class.java
                            )
                            r.favorites = favorites
                            users.add(r)
                        }

                        AccountType.Admin -> {
                            val a = mapper.readValue(accountNode.toString(), Admin::class.java)
                            a.favorites = favorites
                            a.contributions = contributions
                            users.add(a)
                        }

                        AccountType.Contributor -> {
                            val c = mapper.readValue(accountNode.toString(), Contributor::class.java)
                            c.favorites = favorites
                            c.contributions = contributions
                            users.add(c)
                        }
                    }
                } catch (e: IOException) {
                    e.printStackTrace()
                }
            })
            return users
        }

        fun loadActors(): List<Actor> {
            val file = File("src/test/resources/testResources/actors.json");
            val parser = mapper.createParser(Files.readAllBytes(file.toPath()))
            val actors: ArrayNode = mapper.readTree(parser)
            val actorsList = ArrayList<Actor>()
            actors.forEach { actor ->
                actorsList.add(mapper.readValue((actor as ObjectNode).toString(), Actor::class.java))
            }
            return actorsList
        }

        fun loadProductions(): List<Production> {
            val file = File("src/test/resources/testResources/production.json");
            val parser = mapper.createParser(Files.readAllBytes(file.toPath()))
            val productions: ArrayNode = mapper.readTree(parser)
            val productionsList = ArrayList<Production>()
            productions.forEach { production ->
                productionsList.add(
                    when (production.get("type").asText()) {
                        "Movie" -> mapper.readValue((production as ObjectNode).toString(), Movie::class.java)
                        "Series" -> mapper.readValue((production as ObjectNode).toString(), Series::class.java)
                        else -> throw Exception("Invalid production type")
                    }
                )
            }
            return productionsList
        }

        fun loadRequests(): List<Request> {
            val file = File("src/test/resources/testResources/requests.json");
            val parser = mapper.createParser(Files.readAllBytes(file.toPath()))
            val requests: ArrayNode = mapper.readTree(parser)
            val requestsList = ArrayList<Request>()
            requests.forEach { request ->
                requestsList.add(mapper.readValue((request as ObjectNode).toString(), Request::class.java))
            }
            return requestsList
        }
    }
}
