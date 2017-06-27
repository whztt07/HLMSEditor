/****************************************************************************
**
** Copyright (C) 2016 - 2017
**
** This file is generated by the Magus toolkit
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
****************************************************************************/

// Include
#include "magus_core.h"
#include "material_browser.h"
#include "material_thumbs.h"

//****************************************************************************/
MaterialThumbsDockWidget::MaterialThumbsDockWidget(const QString& iconDir, const QString& title, QMainWindow* parent, Qt::WindowFlags flags) :
    QDockWidget (title, parent, flags),
    mParent(parent)
{
    mIconDir = iconDir;
    mInnerMain = new QMainWindow();
    mInnerMain->setMinimumSize(100,100);
    setWidget(mInnerMain);    mTabWidget = new QTabWidget(mInnerMain);
    mInnerMain->setCentralWidget(mTabWidget);
    mTabWidget->show();
    QWidget* oldTitleBar = titleBarWidget();
    setTitleBarWidget(new QWidget());
    delete oldTitleBar;

    // Create PBS selection widget
    mPbsSelection = new Magus::QtDefaultTextureWidget(this);
    mPbsSelection->setTextureSize(QSize(210, 120)); // 210 = 1.78 x 120 (1.78 = 16/9; the width/height ratio of the renderwindow)
    connect(mPbsSelection, SIGNAL(selected(QString,QString)), this, SLOT(handleAssetSelected(QString,QString)));
    connect(mPbsSelection, SIGNAL(doubleClicked(QString,QString)), this, SLOT(handleAssetDoubleClicked(QString,QString)));
    connect(mPbsSelection, SIGNAL(assetDeleted(QString,QString)), this, SLOT(handleAssetDeleted(QString,QString)));

    // Create Unlit selection widget
    mUnlitSelection = new Magus::QtDefaultTextureWidget(this);
    mUnlitSelection->setTextureSize(QSize(210, 120));
    connect(mUnlitSelection, SIGNAL(selected(QString,QString)), this, SLOT(handleAssetSelected(QString,QString)));
    connect(mUnlitSelection, SIGNAL(doubleClicked(QString,QString)), this, SLOT(handleAssetDoubleClicked(QString,QString)));
    connect(mUnlitSelection, SIGNAL(assetDeleted(QString,QString)), this, SLOT(handleAssetDeleted(QString,QString)));

    // -------------------------------------- Fill the assets widget --------------------------------------
    QIcon pbsIcon(mIconDir + ICON_PBS_DATABLOCK_NO_PATH);
    addTab(mPbsSelection, pbsIcon, QString("PBS"));

    QIcon unlitIcon(mIconDir + ICON_UNLIT_DATABLOCK_NO_PATH);
    addTab(mUnlitSelection, unlitIcon, QString("Unlit"));

    // Perform standard functions
    createActions();
    createMenus();
    createToolBars();

    connect(mTabWidget, SIGNAL(currentChanged(int)), this, SLOT(handleTabChanged(int)));
}

//****************************************************************************/
MaterialThumbsDockWidget::~MaterialThumbsDockWidget(void)
{
}

//****************************************************************************/
void MaterialThumbsDockWidget::addTab(QWidget* widget, const QIcon& icon, const QString& name)
{
    mTabWidget->addTab(widget, icon, name);
}

//****************************************************************************/
void MaterialThumbsDockWidget::createActions(void)
{
}

//****************************************************************************/
void MaterialThumbsDockWidget::createMenus(void)
{
}

//****************************************************************************/
void MaterialThumbsDockWidget::createToolBars(void)
{
}

//****************************************************************************/
void MaterialThumbsDockWidget::setResources(const QVector<Magus::QtResourceInfo*>& resources)
{
    clearContent();
    QVectorIterator<Magus::QtResourceInfo*> it(resources);
    it.toFront();
    Magus::QtResourceInfo* info;
    QString baseNameThumb;
    while (it.hasNext())
    {
        info = it.next();
        if (info->resourceType == Magus::TOOL_RESOURCETREE_KEY_TYPE_ASSET)
        {
            baseNameThumb = info->resourceName + QString (".png");
            addAsset(info->topLevelId, 0, 0, THUMBS_PATH.c_str() + baseNameThumb, baseNameThumb);
        }
    }
}

//****************************************************************************/
bool MaterialThumbsDockWidget::addMaterial(const QString& baseNameJson,
                                     const QString& fullNameJson,
                                     const QString& baseNameThumb,
                                     EditorHlmsTypes type)
{
    switch (type)
    {
        case HLMS_PBS:
        {
            addAsset(TOOL_SOURCES_LEVEL_X000_PBS, 0, 0, THUMBS_PATH.c_str() + baseNameThumb, baseNameThumb);
        }
        break;

        case HLMS_UNLIT:
        {
            addAsset(TOOL_SOURCES_LEVEL_X000_UNLIT, 0, 0, THUMBS_PATH.c_str() + baseNameThumb, baseNameThumb);
        }
        break;
    }
    return true;
}

//****************************************************************************/
void MaterialThumbsDockWidget::addAsset(int toplevelId, int parentId, int resourceId, const QString& name, const QString& baseName)
{
    QPixmap pixmap;
    if (Magus::fileExist(name))
        pixmap.load(name);
    else
        pixmap.load(FILE_NO_IMAGE);

    switch (toplevelId)
    {
        case TOOL_SOURCES_LEVEL_X000_PBS:
        {
            // Add pixmap from file to mPbsSelection
            mPbsSelection->addTexture(pixmap, name, baseName, true);
        }
        break;

        case TOOL_SOURCES_LEVEL_X000_UNLIT:
        {
            // Add pixmap from file to mUnlitSelection
            mUnlitSelection->addTexture(pixmap, name, baseName, true);
        }
        break;
    }
}

//****************************************************************************/
void MaterialThumbsDockWidget::selectTab(int toplevelId, int parentId, int resourceId, const QString& name, const QString& baseName)
{
    mTabWidget->setCurrentIndex(toplevelId-1); // Assume that toplevelId follows pattern 1, 2, 3, 4, 5
}

//****************************************************************************/
void MaterialThumbsDockWidget::setSelectThumb(int toplevelId, const QString& baseNameThumb)
{
    switch (toplevelId)
    {
        case TOOL_SOURCES_LEVEL_X000_PBS:
        {
            // Set the widget in mPbsSelection selected
            mPbsSelection->setTextureSelected(baseNameThumb);
        }
        break;

        case TOOL_SOURCES_LEVEL_X000_UNLIT:
        {
            // Set the widget in mUnlitSelection selected
            mUnlitSelection->setTextureSelected(baseNameThumb);
        }
        break;
    }
}

//****************************************************************************/
void MaterialThumbsDockWidget::deleteAsset(const QString& name, bool nameIsNameStr)
{
    // Delete from mPbsSelection
    mPbsSelection->deleteTexture(name, nameIsNameStr);

    // Delete from mUnlitSelection
    mUnlitSelection->deleteTexture(name, nameIsNameStr);
}

//****************************************************************************/
void MaterialThumbsDockWidget::deleteAsset(int toplevelId, const QString& name, bool nameIsNameStr)
{
    switch (toplevelId)
    {
        case TOOL_SOURCES_LEVEL_X000_PBS:
        {
            // Delete from mPbsSelection
            mPbsSelection->deleteTexture(name, nameIsNameStr);
        }
        break;

        case TOOL_SOURCES_LEVEL_X000_UNLIT:
        {
            // Delete from mUnlitSelection
            mUnlitSelection->deleteTexture(name, nameIsNameStr);
        }
        break;
    }
}

//****************************************************************************/
void MaterialThumbsDockWidget::deleteAsset(int toplevelId, const QString& name, const QString& baseName)
{
    switch (toplevelId)
    {
        case TOOL_SOURCES_LEVEL_X000_PBS:
        {
            // Delete from mPbsSelection
            mPbsSelection->deleteTexture(name, baseName);
        }
        break;

        case TOOL_SOURCES_LEVEL_X000_UNLIT:
        {
            // Delete from mUnlitSelection
            mUnlitSelection->deleteTexture(name, baseName);
        }
        break;
    }
}

//****************************************************************************/
void MaterialThumbsDockWidget::filter(const QString& pattern)
{
    resetFilter();
    mPbsSelection->filter(pattern);
    mUnlitSelection->filter(pattern);
}

//****************************************************************************/
void MaterialThumbsDockWidget::resetFilter(void)
{
    mPbsSelection->resetFilter();
    mUnlitSelection->resetFilter();
}

//****************************************************************************/
void MaterialThumbsDockWidget::clearContent(void)
{
    mPbsSelection->clearContent();
    mUnlitSelection->clearContent();
}

//****************************************************************************/
void MaterialThumbsDockWidget::handleTabChanged(int index)
{
    emit tabChanged(index + 1);
}

//****************************************************************************/
void MaterialThumbsDockWidget::handleAssetDeleted(const QString& name, const QString& baseName)
{
    // Note, that these are the thumb image names
    emit assetDeleted(name, baseName);
}

//****************************************************************************/
void MaterialThumbsDockWidget::handleAssetSelected(const QString& name, const QString& baseName)
{
    // Note, that these are the thumb image names
    emit assetSelected(name, baseName);
}

//****************************************************************************/
void MaterialThumbsDockWidget::handleAssetDoubleClicked(const QString& name, const QString& baseName)
{
    // Note, that these are the thumb image names
    emit assetDoubleClicked(name, baseName);
}
