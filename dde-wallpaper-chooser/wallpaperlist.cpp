#include "wallpaperlist.h"
#include "wallpaperitem.h"
#include "constants.h"

#include <QDebug>
#include <QScrollBar>
#include <QWheelEvent>

WallpaperList::WallpaperList(QWidget * parent) :
    QListWidget(parent)
{
    setViewMode(QListView::IconMode);
    setGridSize(QSize(ItemCellWidth, ItemCellHeight));
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWrapping(false);
    setSelectionRectVisible(false);
    setEditTriggers(QListView::NoEditTriggers);
    setAttribute(Qt::WA_TranslucentBackground);
}

void WallpaperList::addWallpaper(const QString &path)
{
    QListWidgetItem * item = new QListWidgetItem(this);
    item->setSizeHint(QSize(ItemWidth, ItemHeight));
    addItem(item);

    WallpaperItem * wallpaper = new WallpaperItem(this, path);
    wallpaper->setFixedSize(item->sizeHint());
    setItemWidget(item, wallpaper);

    connect(wallpaper, &WallpaperItem::pressed, this, &WallpaperList::wallpaperItemPressed);
}

void WallpaperList::wheelEvent(QWheelEvent * event)
{
    QPoint numDegrees = event->angleDelta() / 8;

    if (numDegrees.x()) {
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - numDegrees.x());
    } else if (numDegrees.y()){
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - numDegrees.y());
    }

    event->accept();
}

void WallpaperList::wallpaperItemPressed(WallpaperItem * item)
{
    for (int i = 0; i < count(); i++) {
        QListWidgetItem * ii = this->item(i);
        WallpaperItem * wallpaper = qobject_cast<WallpaperItem*>(itemWidget(ii));

        if (wallpaper) {
            if (wallpaper == item) {
                wallpaper->slideUp();
            } else {
                wallpaper->slideDown();
            }
        }
    }
}
