/*=====================================================================

QGroundControl Open Source Ground Control Station

(c) 2009, 2010 QGROUNDCONTROL PROJECT <http://www.qgroundcontrol.org>

This file is part of the QGROUNDCONTROL project

    QGROUNDCONTROL is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    QGROUNDCONTROL is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with QGROUNDCONTROL. If not, see <http://www.gnu.org/licenses/>.

======================================================================*/

/**
 * @file
 *   @brief Definition of the class QMap3DWidget.
 *
 *   @author Lionel Heng <hengli@student.ethz.ch>
 *
 */

#ifndef QMAP3DWIDGET_H
#define QMAP3DWIDGET_H

#include "Q3DWidget.h"

class CheetahModel;
class FTTextureFont;
class UASInterface;

/**
 * @brief A 3D View widget which displays vehicle-centric information.
 **/
class QMap3DWidget : public Q3DWidget
{
    Q_OBJECT

public:
    explicit QMap3DWidget(QWidget* parent);
    ~QMap3DWidget();

    void buildLayout(void);

    static void display(void* clientData);
    void displayHandler(void);

    static void mouse(Qt::MouseButton button, MouseState state,
                      int32_t x, int32_t y, void* clientData);
    void mouseHandler(Qt::MouseButton button, MouseState state,
                      int32_t x, int32_t y);

    static void timer(void* clientData);
    void timerHandler(void);

    double getTime(void) const;

public slots:
    void setActiveUAS(UASInterface* uas);
    void markTarget(void);

private slots:
    void showGrid(int state);
    void showTrail(int state);
    void recenterCamera(void);
    void toggleLockCamera(int state);

protected:
    UASInterface* uas;

private:
    void drawPlatform(float roll, float pitch, float yaw);
    void drawGrid(void);
    void drawTrail(float x, float y, float z);
    void drawTarget(float x, float y, float z);

    double lastRedrawTime;

    bool displayGrid;
    bool displayTrail;

    typedef struct
    {
        float x;
        float y;
        float z;
    } Pose3D;

    bool lockCamera;
    Pose3D lastUnlockedPose;
    bool updateLastUnlockedPose;
    Pose3D camOffset;

    QVarLengthArray<Pose3D, 10000> trail;

    bool displayTarget;
    Pose3D targetPosition;

    QScopedPointer<CheetahModel> cheetahModel;
    QScopedPointer<FTTextureFont> font;
};

#endif // QMAP3DWIDGET_H
