#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>
#include "model_simulator_game.h"

BOOST_AUTO_TEST_SUITE(TestModel);

BOOST_AUTO_TEST_CASE(TestCases)
{
    GameModel* game = new GameModel();
    BOOST_CHECK_EQUAL(game->addOne(20), 21); 
}



BOOST_AUTO_TEST_CASE(MovePlayerLeftTest)
{
    GameModel game;
    int initialX = game.getPlayer().getX();
    game.movePlayerLeft();
    BOOST_CHECK_EQUAL(game.getPlayer().getX(), initialX - 1);
}

BOOST_AUTO_TEST_CASE(MovePlayerRightTest)
{
    GameModel game;
    int initialX = game.getPlayer().getX();
    game.movePlayerRight();
    BOOST_CHECK_EQUAL(game.getPlayer().getX(), initialX + 1);
}

BOOST_AUTO_TEST_CASE(DoesHitAlienTest)
{
    GameModel game;
    game.getAliens().emplace_back(10, 10);
    BOOST_CHECK_EQUAL(game.doesHitAlien(10, 10), true);
    BOOST_CHECK_EQUAL(game.getAliens().size(), 0);
    BOOST_CHECK_EQUAL(game.getScore(), 10);
    BOOST_CHECK_EQUAL(game.doesHitAlien(5, 5), false);
}

BOOST_AUTO_TEST_CASE(DoesHitPlayerTest)
{
    GameModel* game = new GameModel();
    game->doesHitPlayer(game->getPlayer().getX(), game->getPlayer().getY());
    BOOST_CHECK_EQUAL(game->getPlayer().getLifes(), 3);
    BOOST_CHECK_EQUAL(game->isRunning(), true);
    game->doesHitPlayer(game->getPlayer().getX(), game->getPlayer().getY());
    BOOST_CHECK_EQUAL(game->getPlayer().getLifes(), 2);
    BOOST_CHECK_EQUAL(game->isRunning(), true);
    game->doesHitPlayer(game->getPlayer().getX(), game->getPlayer().getY());
    BOOST_CHECK_EQUAL(game->getPlayer().getLifes(), 1);
    BOOST_CHECK_EQUAL(game->isRunning(), true);
    game->doesHitPlayer(game->getPlayer().getX(), game->getPlayer().getY());
    BOOST_CHECK_EQUAL(game->getPlayer().getLifes(), 0);
    BOOST_CHECK_EQUAL(game->isRunning(), false);
}

BOOST_AUTO_TEST_CASE(MoveAliensTest)
{
    GameModel game;
    game.moveAliens();
    BOOST_CHECK_EQUAL(game.getAliens().size(), 0);
    game.getAliens().emplace_back(10, 10);
    game.moveAliens();
    BOOST_CHECK_EQUAL(game.getAliens().size(), 1);
    BOOST_CHECK_EQUAL(game.getAliens()[0].getX(), 11);
    BOOST_CHECK_EQUAL(game.getAliens()[0].getY(), 10);
}


BOOST_AUTO_TEST_CASE(DeleteShotTest)
{
    GameModel game;
    game.getShots().emplace_back(10, 10);
    game.deleteShot(10, 10);
    BOOST_CHECK_EQUAL(game.getShots().size(), 0);
}

BOOST_AUTO_TEST_CASE(MoveShotsTest)
{
    GameModel game;
    game.getShots().emplace_back(10, 10, 1);
    game.moveShots();
    BOOST_CHECK_EQUAL(game.getShots().size(), 1);
    BOOST_CHECK_EQUAL(game.getShots()[0].getY(), 11);
}


BOOST_AUTO_TEST_CASE(IncreaseScoreTest)
{
    GameModel game;
    game.increaseScore();
    BOOST_CHECK_EQUAL(game.getScore(), 10);
}

BOOST_AUTO_TEST_CASE(MoveOneUpsTest)
{
    GameModel game;
    game.moveOneUps();
    BOOST_CHECK_EQUAL(game.getOneUps().size(), 0);
    game.getOneUps().emplace_back(10, 10);
    game.moveOneUps();
    BOOST_CHECK_EQUAL(game.getOneUps().size(), 1);
    BOOST_CHECK_EQUAL(game.getOneUps()[0].getY(), 11);
}


BOOST_AUTO_TEST_CASE(DeleteOneUpTest)
{
    GameModel game;
    game.getOneUps().emplace_back(10, 10);
    game.deleteOneUp(10, 10);
    BOOST_CHECK_EQUAL(game.getOneUps().size(), 0);
}

BOOST_AUTO_TEST_CASE(NextLevelTest)
{
    GameModel game;
    game.nextLevel();
    BOOST_CHECK_EQUAL(game.getAliens().size(), 20);
    BOOST_CHECK_EQUAL(game.getAliens()[0].getX() >= 2 && game.getAliens()[0].getX() <= 77, true);
    BOOST_CHECK_EQUAL(game.getAliens()[0].getY(), 3);
}

BOOST_AUTO_TEST_CASE(DefineSlotsTest)
{
    GameModel game;
    std::map<int, std::pair<int, int>> slots = game.defineSlots();
    BOOST_CHECK_EQUAL(slots.size(), 36);
    BOOST_CHECK_EQUAL(slots[0].first, 2);
    BOOST_CHECK_EQUAL(slots[0].second, 3);
    BOOST_CHECK_EQUAL(slots[79].first, 0);
    BOOST_CHECK_EQUAL(slots[79].second, 0);
}

BOOST_AUTO_TEST_SUITE_END();