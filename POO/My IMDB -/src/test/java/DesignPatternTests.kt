import CheckerUtils.Companion.checkBuilder
import CheckerUtils.Companion.checkFactory
import CheckerUtils.Companion.checkObserver
import CheckerUtils.Companion.checkSingleton
import CheckerUtils.Companion.checkStrategy
import CheckerUtils.Companion.checkSubject
import com.fasterxml.jackson.databind.ObjectMapper
import com.fasterxml.jackson.databind.node.NullNode
import com.fasterxml.jackson.databind.node.ObjectNode
import org.junit.jupiter.api.BeforeAll
import org.junit.jupiter.api.Test
import java.lang.RuntimeException
import java.nio.file.Files
import javax.management.RuntimeErrorException
import kotlin.io.path.Path
import kotlin.math.abs

class DesignPatternsChecker {
    @Test fun singletonTest() {
        val maxScore = 5.0f

        val mainSingleton : Class<*>? = (singletons.find { it.simpleName == "IMDB" })
        singletons = singletons.filter { it.simpleName != "IMDB" }
        if (mainSingleton == null) {
            println("IMDB singleton was not found \t\t\t\t\t\t\t\t0.0/$maxScore")
            assert(false)
        }

        val score = checkSingleton(mainSingleton!!, maxScore)
        if (score == maxScore) {
            println("Singleton ${mainSingleton.simpleName} is implemented correctly\t\t\t$score/$maxScore")
        } else {
            println("Singleton ${mainSingleton.simpleName} is not implemented correctly\t\t\t$score/$maxScore")
            assert(false)
        }

        for(singleton in singletons) {
            println()
            if (checkSingleton(singleton, maxScore) == maxScore) {
                println("Singleton ${singleton.simpleName} is implemented correctly")
            } else {
                println("Singleton ${singleton.simpleName} is not implemented correctly")
            }
        }
    }
    @Test fun builderTest() {
        val maxScore = 10.0f

        val mainBuilder : Pair<Class<*>, Class<*>?> =
            builders.find { it.first.simpleName == "InformationBuilder" && it.second != null && it.second!!.simpleName == "Information" ||
                            it.first.simpleName == "Information"        && it.second == null } ?:
                throw RuntimeException("InformationBuilder builder was not found \t\t\t\t\t\t0.0/$maxScore")
        builders = builders.filter { it != mainBuilder }

        val score = checkBuilder(mainBuilder.first, maxScore, mainBuilder.second)
        if (score == maxScore) {
            println("Builder ${mainBuilder.first.simpleName} is implemented correctly\t\t\t$score/$maxScore")
        } else {
            println("Builder ${mainBuilder.first.simpleName} is not implemented correctly\t\t\t$score/$maxScore")
            assert(false)
        }

        for(builder in builders) {
            val bld = builder.first
            val blt = builder.second
            println()
            if (checkBuilder(bld, maxScore, blt) == maxScore) {
                println("Builder ${builder.first.simpleName} is implemented correctly")
            } else {
                println("Builder ${builder.first.simpleName} is not implemented correctly")
            }
        }
    }
    @Test fun factoryTest() {
        val maxScore = 10.0f

        val mainFactory : Pair<Class<*>, Class<*>> = factories.find { it.first.simpleName == "UserFactory" && it.second.simpleName == "AccountType" } ?:
            throw RuntimeException("UserFactory factory was not found \t\t\t\t\t\t\t\t0.0/$maxScore")
        factories = factories.filter { it != mainFactory }

        val score = checkFactory(mainFactory.first, mainFactory.second, maxScore)

        if (abs(score - maxScore) < 0.001f) {
            println("Factory ${mainFactory.first.simpleName} is implemented correctly\t\t\t$score/$maxScore")
        } else {
            println("Factory ${mainFactory.first.simpleName} is not implemented correctly\t\t\t$score/$maxScore")
            assert(false)
        }

        for(factory in factories) {
            println()
            if (checkFactory(factory.first, factory.second, maxScore) == maxScore) {
                println("Factory ${factory.first.simpleName} is implemented correctly")
            } else {
                println("Factory ${factory.first.simpleName} is not implemented correctly")
            }
        }
    }
    @Test fun strategyTest() {
        val maxScore = 5.0f
        try {
            val strategy = Class.forName("org.example.ExperienceStrategy")
            val score = checkStrategy(strategy, maxScore)
            if (abs(score - maxScore) < 0.001f) {
                println("Strategy ${strategy.simpleName} is implemented correctly\t\t\t$score/$maxScore")
            } else {
                println("Strategy ${strategy.simpleName} is not implemented correctly\t\t\t$score/$maxScore")
                assert(false)
            }
        } catch (e: ClassNotFoundException) {
            println("Strategy was not found\t\t\t\t\t\t\t0.0/$maxScore")
            assert(false)
        }
    }
    @Test fun observerTest() {
        val maxScore = 20.0f
        var totalScore = 0.0f

        val observer: Class<*>
        val subject: Class<*>
        try {
            observer = Class.forName("org.example.Observer")
        } catch (e: ClassNotFoundException) {
            println("Observer was not found\t\t\t\t\t\t\t0.0/$maxScore")
            assert(false)
            return
        }
        try {
            subject = Class.forName("org.example.Subject")
        } catch (e: ClassNotFoundException) {
            println("Subject was not found\t\t\t\t\t\t\t0.0/$maxScore")
            assert(false)
            return
        }

        if (!observer.isInterface) {
            println("Observer should be an interface\t\t\t\t\t\t\t0.0/$maxScore")
            assert(false)
        }

        if (!subject.isInterface) {
            println("Subject should be an interface\t\t\t\t\t\t\t0.0/$maxScore")
            assert(false)
        }

        if(observer.methods.size != 1 || observer.methods[0].name != "update") {
            println("Observer does not have the right structure")
        } else {
            totalScore += maxScore / 8.0f
        }

        if(subject.methods.size != 3 ||
            subject.methods.none{ it.name == "subscribe" || it.name == "addObserver" } ||
            subject.methods.none{ it.name == "unsubscribe" || it.name == "removeObserver" } ||
            subject.methods.none{ it.name == "notify" || it.name == "notifyObservers" }) {
            println("Subject does not have the right structure")
        } else {
            totalScore += maxScore / 8.0f
        }

        for (obs in observers) {
            val score = checkObserver(obs,  maxScore / 4.0f / observers.size)
            if (abs(score - maxScore / 4.0f / observers.size) < 0.001f) {
                println("Observer ${obs.simpleName} is implemented correctly")
            } else {
                println("Observer ${obs.simpleName} is not implemented correctly")
            }
            totalScore += score
        }

        for (sub in subjects) {
            val score = checkSubject(sub,  maxScore / 2.0f / subjects.size)
            if (abs(score - maxScore / 2.0f / subjects.size) < 0.001f) {
                println("Subject ${sub.simpleName} is implemented correctly")
            } else {
                println("Subject ${sub.simpleName} is not implemented correctly")
            }
            totalScore += score
        }

        println("Total score for observer pattern: $totalScore/$maxScore")

        if (abs(totalScore - maxScore) > 0.001f) {
            assert(false)
        }

    }
    companion object {

        private lateinit var singletons: List<Class<*>>
        private lateinit var builders: List<Pair<Class<*>, Class<*>?>>
        private lateinit var factories: List<Pair<Class<*>, Class<*>>>
        private lateinit var observers: List<Class<*>>
        private lateinit var subjects: List<Class<*>>


        @JvmStatic
        @BeforeAll
        fun init() {
            val bytes = Files.readAllBytes(Path("src/test/resources/checkerConfig.json"))
            val mapper = ObjectMapper()
            val config = mapper.createParser(bytes)
            val objectNode: ObjectNode = mapper.readTree(config)

            if (objectNode["singletons"] == null ||
                objectNode["builders"] == null ||
                objectNode["factories"] == null ||
                objectNode["observers"] == null ||
                objectNode["observers"][0]["observers"] == null ||
                objectNode["observers"][0]["subjects"] == null)
                throw AssertionError("Config file structure was changed. Please redownload the config file from the repository and try again.")

            singletons = objectNode["singletons"].map { Class.forName(it.asText()) }
            builders = objectNode["builders"].map {
                if (it["built"] is NullNode) {
                    Pair(Class.forName(it["builder"].asText()), null)
                } else {
                Pair(Class.forName(it["builder"].asText()), Class.forName(it["built"].asText())) }
            }
            factories = objectNode["factories"].map { Pair(Class.forName(it["name"].asText()), Class.forName(it["enum"].asText())) }
            observers = objectNode["observers"][0]["observers"].map { Class.forName(it.asText()) }
            subjects = objectNode["observers"][0]["subjects"].map { Class.forName(it.asText()) }

        }
    }
}