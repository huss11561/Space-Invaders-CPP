#define BOOST_TEST_MODULE test
#include <boost/test/included/unit_test.hpp>
#include "bullet.h"
#include "alien.h"
#include "stone.h"

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
    Stone s(5, 10,5);
    BOOST_CHECK_EQUAL(s.getX(), 10);
    BOOST_CHECK_EQUAL(s.getY(), 5);
}

BOOST_AUTO_TEST_CASE(test_set_position_stone) {
    Stone s(5, 10,5);
    s.setX(15);
    s.setY(20);
    BOOST_CHECK_EQUAL(s.getX(), 15);
    BOOST_CHECK_EQUAL(s.getY(), 20);
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


