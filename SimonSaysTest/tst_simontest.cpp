#include <QtTest>
#include "simon.h"

// add necessary includes here

class SimonTest : public QObject {
    Q_OBJECT

    public:
        SimonTest();
        ~SimonTest();

    private slots:
        void testRandomColor();

    private:
        Player player = Player();
        Simon simon = Simon(player);

};

SimonTest::SimonTest() {}

SimonTest::~SimonTest() {}


// congrats it's a test
void SimonTest::testRandomColor() {
    string color = simon.chooseRandomColor();

    if (color == "red" || color == "green" || color == "blue" || color == "yellow") {
        QVERIFY(true);
    } else {
        QVERIFY(false);
    }
}

QTEST_APPLESS_MAIN(SimonTest)

#include "tst_simontest.moc"
