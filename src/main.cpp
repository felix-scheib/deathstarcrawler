#include "engine/management/dungeoncrawler.h"
#include "ui/gui/graphicalui.h"

#include <memory>
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication application(argc, argv);

    srand (time(NULL));

    std::unique_ptr<DungeonCrawler> game = std::make_unique<DungeonCrawler>();

    //game->play();
    game->active();

    application.closeAllWindows();
    application.quit();

    return 0;
}
