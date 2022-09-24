#ifndef GLOBALTHEMECREATOR_H
#define GLOBALTHEMECREATOR_H

#include <QScopedPointer>
#include <QDialog>

namespace Ui
{
class globalThemeCreator;
}

/**
 * @todo write docs
 */
class globalThemeCreator : public QDialog
{
    Q_OBJECT

public:
    /**
     * @todo write docs
     */

private:
    QScopedPointer<Ui::globalThemeCreator> m_ui;
};

#endif // GLOBALTHEMECREATOR_H
// kate: indent-mode cstyle; indent-width 1; replace-tabs on; ;
