#define BOOST_TEST_MODULE test
#include <boost/test/included/unit_test.hpp>
#include "model_simulator_game.h"
#include "bullet.h"
#include "alien.h"
#include "stone.h"
#include "controller_console.h"


// BULLET TESTS
BOOST_AUTO_TEST_CASE(test_initial_position_bullet) {
    Bullet b(10, 20, true);
    BOOST_TEST(b.getX() == 10);
    BOOST_TEST(b.getY() == 20);
    BOOST_TEST(b.isFromPlayer() == true);
}

BOOST_AUTO_TEST_CASE(test_move_bullet) {
    Bullet b(10, 20, true);
    b.move(); // Assuming this decreases y by 1
    BOOST_TEST(b.getY() == 19);
}

BOOST_AUTO_TEST_CASE(test_isFromPlayer_bullet) {
    Bullet b(10, 20, true);
    BOOST_TEST(b.isFromPlayer() == true);
    b = Bullet(10, 20, false);
    BOOST_TEST(b.isFromPlayer() == false);
}

// ALIEN TESTS
BOOST_AUTO_TEST_CASE(test_initial_position_alien) {
    Alien a(5, 10);
    BOOST_CHECK_EQUAL(a.getX(), 10);
    BOOST_CHECK_EQUAL(a.getY(), 5);
}

BOOST_AUTO_TEST_CASE(test_set_position_alien) {
    Alien a(5, 10);
    a.setX(15);
    a.setY(20);
    BOOST_CHECK_EQUAL(a.getX(), 15);
    BOOST_CHECK_EQUAL(a.getY(), 20);
}

BOOST_AUTO_TEST_CASE(test_alive_status_alien) {
    Alien a(5, 10);
    BOOST_CHECK(a.isAlive());

    a.setAlive(false);
    BOOST_CHECK(!a.isAlive());

    a.setAlive(true);
    BOOST_CHECK(a.isAlive());
}


// STONE TESTS 
BOOST_AUTO_TEST_CASE(test_initial_position_stone) {
    Stone s(10, 5,5);
    BOOST_CHECK_EQUAL(s.getX(), 10);
    BOOST_CHECK_EQUAL(s.getY(), 5);
}


BOOST_AUTO_TEST_CASE(test_health_status_stone) {
    Stone s(5, 10,5);
    BOOST_CHECK(s.getHealth() == 5);
}

BOOST_AUTO_TEST_CASE(test_takeDamage_stone) {
    Stone s(5, 10,5);
    s.takeDamage();
    BOOST_CHECK(s.getHealth() == 4);
    s.takeDamage();
    BOOST_CHECK(s.getHealth() == 3);

}

BOOST_AUTO_TEST_CASE(test_broken_stone) {
    Stone s(5, 10,5);
    BOOST_CHECK(!s.isBroken());
    s.takeDamage();
    BOOST_CHECK(!s.isBroken());
    s.takeDamage();
    BOOST_CHECK(!s.isBroken());
    s.takeDamage();
    BOOST_CHECK(!s.isBroken());
    s.takeDamage();
    BOOST_CHECK(!s.isBroken());
    s.takeDamage();
    BOOST_CHECK(s.isBroken());
}


// GAME MODEL TESTS
BOOST_AUTO_TEST_CASE(test_initial_position_game_model) {
    GameModel m;
    BOOST_CHECK_EQUAL(m.getPlayer().getX(), 20);
    BOOST_CHECK_EQUAL(m.getPlayer().getY(), 24);
}

BOOST_AUTO_TEST_CASE(test_set_position_game_model) {
    GameModel m;
    m.getPlayer().setX(10);
    m.getPlayer().setY(20);
    BOOST_CHECK_EQUAL(m.getPlayer().getX(), 10);
    BOOST_CHECK_EQUAL(m.getPlayer().getY(), 20);
}

BOOST_AUTO_TEST_CASE(test_initial_score_game_model) {
    GameModel m;
    BOOST_CHECK_EQUAL(m.getPlayer().getPoints(), 0);
}

BOOST_AUTO_TEST_CASE(test_set_score_game_model) {
    GameModel m;
    m.getPlayer().setPoints(10);
    BOOST_CHECK_EQUAL(m.getPlayer().getPoints(), 10);
}

BOOST_AUTO_TEST_CASE(test_initial_lives_game_model) {
    GameModel m;
    BOOST_CHECK_EQUAL(m.getPlayer().getLife(), 5);
}

BOOST_AUTO_TEST_CASE(test_set_lives_game_model) {
    GameModel m;
    m.getPlayer().setLife(3);
    BOOST_CHECK_EQUAL(m.getPlayer().getLife(), 3);
}

// Collision tests
BOOST_AUTO_TEST_CASE(test_checkCollision) {
    GameModel gameModel;

    BOOST_CHECK(gameModel.checkCollision(10, 20, 10, 20) == true);
    BOOST_CHECK(gameModel.checkCollision(10, 20, 15, 20) == false);
    BOOST_CHECK(gameModel.checkCollision(10, 20, 10, 25) == false);
    BOOST_CHECK(gameModel.checkCollision(10, 20, 15, 25) == false);
}

//Die testklasse zum größtenteil mit KI (chatpt) zusammen geschrieben, dabei habe ich foldegende prompts benutztz : "Hier ist miene Makefile, die ich benutze (copy&paste), bitte schreibe mir einen testdatei, die die Klasse Alien (copy paste vom, header file) testet und benutze dabei nur die boost library" Erste Ausgab war so : #define BOOST_TEST_MODULE AlienTest
/*#include <boost/test/included/unit_test.hpp>
#include "alien.h"

BOOST_AUTO_TEST_CASE(test_initial_position) {
    Alien a(5, 10);
    BOOST_CHECK_EQUAL(a.getX(), 10);
    BOOST_CHECK_EQUAL(a.getY(), 5);
}

BOOST_AUTO_TEST_CASE(test_set_position) {
    Alien a(5, 10);
    a.setX(15);
    a.setY(20);
    BOOST_CHECK_EQUAL(a.getX(), 15);
    BOOST_CHECK_EQUAL(a.getY(), 20);
}

BOOST_AUTO_TEST_CASE(test_alive_status) {
    Alien a(5, 10);
    BOOST_CHECK(a.isAlive());

    a.setAlive(false);
    BOOST_CHECK(!a.isAlive());

    a.setAlive(true);
    BOOST_CHECK(a.isAlive());
}
*/ 
//dann habe ich anhandessen weitere tests mit dem Muster geschrieben und haben dabei vieles von github copilot ergänzen lassen.
