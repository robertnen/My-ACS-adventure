import CheckerUtils.Companion.checkEquals
import CheckerUtils.Companion.loadActors
import CheckerUtils.Companion.loadProductions
import CheckerUtils.Companion.loadRequests
import CheckerUtils.Companion.loadUsers
/*
 *   FIXME: Pentru a functiona checker-ul aceste clase trebuie sa existe si sa aiba functiile si membrii necesari
 */
import org.example.Actor
import org.example.IMDB
import org.example.Request
import org.example.Movie
import org.example.Production
import org.example.Series
import org.example.Admin
import org.example.Contributor
import org.example.Regular
import org.example.User

import org.junit.jupiter.api.Assertions
import org.junit.jupiter.api.Test
import java.lang.reflect.Modifier

class JsonDataLoadChecker {
    @Test
    fun loadTest() {
        IMDB.getInstance().run()
        val imdb = IMDB.getInstance()
        val fields = imdb.javaClass.declaredFields
        for (field in fields) {
            if (!Modifier.isPrivate(field.modifiers)) {
                throw AssertionError("All fields in IMDB should be private")
            } else {
                field.isAccessible = true
            }
            when (field.name) {
                "users" -> {
                    Assertions.assertEquals(
                        field.type,
                        MutableList::class.java,
                        "users field should be of type List<User>"
                    )
                    when (val fieldValue = field.get(imdb)) {
                        null -> throw AssertionError("users field should not be null")
                        is List<*> -> {
                            @Suppress("unchecked_cast")
                            val users = fieldValue as List<User<*>>
                            val testUsers = loadUsers()
                            Assertions.assertEquals(users.size, testUsers.size)
                            users.zip(testUsers).forEach { (user, testUser): Pair<User<*>, User<*>> ->
                                when (user) {
                                    is Regular<*> -> Assertions.assertTrue(
                                        checkEquals(user.javaClass, user, testUser),
                                        "Regular $user is not equal to $testUser"
                                    )
                                    is Contributor<*> -> Assertions.assertTrue(
                                        checkEquals(user.javaClass, user, testUser),
                                        "Contributor $user is not equal to $testUser"
                                    )
                                    is Admin<*> -> Assertions.assertTrue(
                                        checkEquals(user.javaClass, user, testUser),
                                        "Admin $user is not equal to $testUser"
                                    )
                                }
                            }
                        }
                    }
                }

                "actors" -> {
                    Assertions.assertEquals(
                        field.type,
                        MutableList::class.java,
                        "actors field should be of type List<Actor>"
                    )
                    when (val fieldValue = field.get(imdb)) {
                        null -> throw AssertionError("actors field should not be null")
                        is List<*> -> {
                            @Suppress("unchecked_cast")
                            val actors = fieldValue as List<Actor>
                            val testActors = loadActors()
                            Assertions.assertEquals(actors.size, testActors.size)
                            actors.zip(testActors).forEach { (actor, testActor): Pair<Actor, Actor> ->
                                Assertions.assertTrue(
                                    checkEquals(actor.javaClass, actor, testActor),
                                    "Actor $actor is not equal to $testActor"
                                )
                            }
                        }
                    }
                }

                "productions" -> {
                    Assertions.assertEquals(
                        field.type,
                        MutableList::class.java,
                        "productions field should be of type List<Production>"
                    )
                    when (val fieldValue = field.get(imdb)) {
                        null -> throw AssertionError("productions field should not be null")
                        is List<*> -> {
                            @Suppress("unchecked_cast")
                            val productions = fieldValue as List<Production>
                            val testProductions = loadProductions()
                            Assertions.assertEquals(productions.size, testProductions.size)
                            productions.zip(testProductions).forEach { (production, testProduction): Pair<Production, Production> ->
                                when (production) {
                                    is Movie -> Assertions.assertTrue(
                                        checkEquals(
                                            production.javaClass,
                                            production,
                                            testProduction
                                        ), "Movie $production is not equal to $testProduction"
                                    )
                                    is Series -> Assertions.assertTrue(
                                        checkEquals(
                                            production.javaClass,
                                            production,
                                            testProduction
                                        ), "Series $production is not equal to $testProduction"
                                    )
                                } }
                        }
                    }
                }

                "requests" -> {
                    Assertions.assertEquals(
                        field.type,
                        MutableList::class.java,
                        "requests field should be of type List<Request>"
                    )
                    when (val fieldValue = field.get(imdb)) {
                        null -> throw AssertionError("requests field should not be null")
                        is List<*> -> {
                            @Suppress("unchecked_cast")
                            val requests = fieldValue as List<Request>
                            val testRequests = loadRequests()
                            Assertions.assertEquals(requests.size, testRequests.size)
                            requests.zip(testRequests).forEach { (request, testRequest): Pair<Request, Request> ->
                                Assertions.assertTrue(
                                    checkEquals(request.javaClass, request, testRequest),
                                    "Request $request is not equal to $testRequest"
                                )
                            }
                        }
                    }

                }
            }
        }
    }
}