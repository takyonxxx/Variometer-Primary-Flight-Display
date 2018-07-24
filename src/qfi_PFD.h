/***************************************************************************//**
 * @file qfi_PFD.h
 * @author Marek M. Cel <marekcel@marekcel.pl>
 * @author Dave Culp <daveculp@cox.net>
 *
 * @section LICENSE
 *
 * Copyright (C) 2018 Marek M. Cel, Dave Culp
 *
 * This file is part of QFlightInstruments. You can redistribute and modify it
 * under the terms of GNU General Public License as published by the Free
 * Software Foundation; either version 3 of the License, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 * Further information about the GNU General Public License can also be found
 * on the world wide web at http://www.gnu.org.
 *
 * ---
 *
 * Copyright (C) 2018 Marek M. Cel, Dave Culp
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/
#ifndef QFI_PFD_H
#define QFI_PFD_H

////////////////////////////////////////////////////////////////////////////////
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsSvgItem>

////////////////////////////////////////////////////////////////////////////////

/** Primary Flight Display widget. */
class qfi_PFD : public QGraphicsView
{
    Q_OBJECT

public:

    /** Altimeter pressure units. */
    enum PressureUnit
    {
        STD = 0,    ///< standard (displays STD instead of numerical value)
        MB,         ///< milibars
        IN          ///< inches of mercury
    };

    /** Constructor. */
    explicit qfi_PFD( QWidget *parent = 0 );

    /** Destructor. */
    ~qfi_PFD();

    /** Reinitiates widget. */
    void reinit();

    /** Refreshes (redraws) widget. */
    void update();

    /** @param roll angle [deg] */
    inline void setRoll( qreal roll )
    {
        m_adi->setRoll( roll );
    }

    /** @param pitch angle [deg] */
    inline void setPitch( qreal pitch )
    {
        m_adi->setPitch( pitch );
    }

    /**
     * @param angle of attack [deg]
     * @param angle of sideslip [deg]
     * @param flight path marker visibility */
    inline void setFlightPathMarker( qreal aoa, qreal sideslip, bool visible = true )
    {
        m_adi->setFlightPathMarker( aoa, sideslip, visible );
    }

    /** @param normalized slip or skid (range from -1.0 to 1.0) */
    inline void setSlipSkid( qreal slipSkid )
    {
        m_adi->setSlipSkid( slipSkid );
    }

    /**
     * @param normalized turn rate (range from -1.0 to 1.0),
     * hash marks positions are set to be -0.5 and 0.5 */
    inline void setTurnRate( qreal turnRate )
    {
        m_adi->setTurnRate( turnRate );
    }

    /**
     * @param normalized horizontal deviation bar position (range from -1.0 to 1.0)
     * @param horizontal deviation bar visibility */
    inline void setBarH( qreal barH, bool visible = true )
    {
        m_adi->setBarH( barH, visible );
    }

    /**
     * @param normalized vertical deviation bar position (range from -1.0 to 1.0)
     * @param vertical deviation bar visibility */
    inline void setBarV( qreal barV, bool visible = true )
    {
        m_adi->setBarV( barV, visible );
    }

    /**
     * @param normalized horizontal deviation dot position (range from -1.0 to 1.0)
     * @param horizontal deviation dot visibility */
    inline void setDotH( qreal dotH, bool visible = true )
    {
        m_adi->setDotH( dotH, visible );
    }

    /**
     * @param normalized vertical deviation dot position (range from -1.0 to 1.0)
     * @param vertical deviation dot visibility */
    inline void setDotV( qreal dotV, bool visible = true )
    {
        m_adi->setDotV( dotV, visible );
    }

    /** @param altitude (dimensionless numeric value) */
    inline void setAltitude( qreal altitude )
    {
        m_alt->setAltitude( altitude );
    }

    /**
     * @param pressure (dimensionless numeric value)
     * @param pressure unit according to GraphicsPFD::PressureUnit */
    inline void setPressure( qreal pressure, PressureUnit pressureUnit )
    {
        m_alt->setPressure( pressure, pressureUnit );
    }

    /** @param airspeed (dimensionless numeric value) */
    inline void setAirspeed( qreal airspeed )
    {
        m_asi->setAirspeed( airspeed );
    }

    /** @param Mach number */
    inline void setMachNo( qreal machNo )
    {
        m_asi->setMachNo( machNo );
    }

    /** @param heading [deg] */
    inline void setHeading( qreal heading )
    {
        m_hsi->setHeading( heading );
    }

    /** @param climb rate (dimensionless numeric value)  */
    inline void setClimbRate( qreal climbRate )
    {
        m_vsi->setClimbRate( climbRate );
    }

    /** @param ident (4-letter text) */
    inline void setIdent( const QString &ident, bool visible = false )
    {
        m_ils->setIdentifier( ident, visible );
    }

    /** @param distance [nautical miles] */
    inline void setDistance( qreal dist, bool visible = false )
    {
        m_ils->setDistance( dist, visible );
    }

protected:

    void resizeEvent( QResizeEvent *event );

private:

    class ADI
    {
    public:

        ADI( QGraphicsScene *scene );
        void init( qreal scaleX, qreal scaleY );
        void update( qreal scaleX, qreal scaleY );
        void setRoll( qreal roll );
        void setPitch( qreal pitch );
        void setFlightPathMarker( qreal aoa, qreal sideslip, bool visible = true );
        void setSlipSkid( qreal slipSkid );
        void setTurnRate( qreal turnRate );
        void setBarH( qreal barH, bool visible = true );
        void setBarV( qreal barV, bool visible = true );
        void setDotH( qreal dotH, bool visible = true );
        void setDotV( qreal dotV, bool visible = true );

    private:

        QGraphicsScene *m_scene;

        QGraphicsSvgItem *m_itemBack;
        QGraphicsSvgItem *m_itemLadd;
        QGraphicsSvgItem *m_itemRoll;
        QGraphicsSvgItem *m_itemSlip;
        QGraphicsSvgItem *m_itemTurn;
        QGraphicsSvgItem *m_itemPath;
        QGraphicsSvgItem *m_itemMark;
        QGraphicsSvgItem *m_itemBarH;
        QGraphicsSvgItem *m_itemBarV;
        QGraphicsSvgItem *m_itemDotH;
        QGraphicsSvgItem *m_itemDotV;
        QGraphicsSvgItem *m_itemMask;
        QGraphicsSvgItem *m_itemScaleH;
        QGraphicsSvgItem *m_itemScaleV;

        qreal m_roll;
        qreal m_pitch;
        qreal m_angleOfAttack;
        qreal m_sideslipAngle;
        qreal m_slipSkid;
        qreal m_turnRate;
        qreal m_barH;
        qreal m_barV;
        qreal m_dotH;
        qreal m_dotV;

        bool m_pathValid;

        bool m_pathVisible;
        bool m_barHVisible;
        bool m_barVVisible;
        bool m_dotHVisible;
        bool m_dotVVisible;

        qreal m_laddDeltaX_new;
        qreal m_laddDeltaX_old;
        qreal m_laddBackDeltaX_new;
        qreal m_laddBackDeltaX_old;
        qreal m_laddBackDeltaY_new;
        qreal m_laddBackDeltaY_old;
        qreal m_laddDeltaY_new;
        qreal m_laddDeltaY_old;
        qreal m_slipDeltaX_new;
        qreal m_slipDeltaX_old;
        qreal m_slipDeltaY_new;
        qreal m_slipDeltaY_old;
        qreal m_turnDeltaX_new;
        qreal m_turnDeltaX_old;
        qreal m_pathDeltaX_new;
        qreal m_pathDeltaX_old;
        qreal m_pathDeltaY_new;
        qreal m_pathDeltaY_old;
        qreal m_markDeltaX_new;
        qreal m_markDeltaX_old;
        qreal m_markDeltaY_new;
        qreal m_markDeltaY_old;
        qreal m_barHDeltaX_new;
        qreal m_barHDeltaX_old;
        qreal m_barVDeltaY_new;
        qreal m_barVDeltaY_old;
        qreal m_dotHDeltaX_new;
        qreal m_dotHDeltaX_old;
        qreal m_dotVDeltaY_new;
        qreal m_dotVDeltaY_old;

        qreal m_scaleX;
        qreal m_scaleY;

        const qreal m_originalPixPerDeg;
        const qreal m_deltaLaddBack_max;
        const qreal m_deltaLaddBack_min;
        const qreal m_maxSlipDeflection;
        const qreal m_maxTurnDeflection;
        const qreal m_maxBarsDeflection;
        const qreal m_maxDotsDeflection;

        QPointF m_originalAdiCtr;
        QPointF m_originalBackPos;
        QPointF m_originalLaddPos;
        QPointF m_originalRollPos;
        QPointF m_originalSlipPos;
        QPointF m_originalTurnPos;
        QPointF m_originalPathPos;
        QPointF m_originalBarHPos;
        QPointF m_originalBarVPos;
        QPointF m_originalDotHPos;
        QPointF m_originalDotVPos;
        QPointF m_originalScaleHPos;
        QPointF m_originalScaleVPos;

        const int m_backZ;
        const int m_laddZ;
        const int m_rollZ;
        const int m_slipZ;
        const int m_pathZ;
        const int m_barsZ;
        const int m_dotsZ;
        const int m_scalesZ;
        const int m_maskZ;
        const int m_turnZ;

        void reset();
        void updateLadd( qreal delta, qreal sinRoll, qreal cosRoll );
        void updateLaddBack( qreal delta, qreal sinRoll, qreal cosRoll );
        void updateRoll();
        void updateSlipSkid( qreal sinRoll, qreal cosRoll );
        void updateTurnRate();
        void updateFlightPath();
        void updateBars();
        void updateDots();
    };

    class ALT
    {
    public:

        ALT( QGraphicsScene *scene );
        void init( qreal scaleX, qreal scaleY );
        void update( qreal scaleX, qreal scaleY );
        void setAltitude( qreal altitude );
        void setPressure( qreal pressure, int pressureUnit );

    private:

        QGraphicsScene *m_scene;

        QGraphicsSvgItem  *m_itemBack;
        QGraphicsSvgItem  *m_itemScale1;
        QGraphicsSvgItem  *m_itemScale2;
        QGraphicsTextItem *m_itemLabel1;
        QGraphicsTextItem *m_itemLabel2;
        QGraphicsTextItem *m_itemLabel3;
        QGraphicsSvgItem  *m_itemGround;
        QGraphicsSvgItem  *m_itemFrame;
        QGraphicsTextItem *m_itemAltitude;
        QGraphicsTextItem *m_itemPressure;

        QColor m_frameTextColor;
        QColor m_pressTextColor;
        QColor m_labelsColor;

        QFont  m_frameTextFont;
        QFont  m_pressTextFont;
        QFont  m_labelsFont;

        qreal m_altitude;
        qreal m_pressure;

        int m_pressureUnit;

        qreal m_scale1DeltaY_new;
        qreal m_scale1DeltaY_old;
        qreal m_scale2DeltaY_new;
        qreal m_scale2DeltaY_old;
        qreal m_groundDeltaY_new;
        qreal m_groundDeltaY_old;
        qreal m_labelsDeltaY_new;
        qreal m_labelsDeltaY_old;

        qreal m_scaleX;
        qreal m_scaleY;

        const qreal m_originalPixPerAlt;
        const qreal m_originalScaleHeight;
        const qreal m_originalLabelsX;
        const qreal m_originalLabel1Y;
        const qreal m_originalLabel2Y;
        const qreal m_originalLabel3Y;

        QPointF m_originalBackPos;
        QPointF m_originalScale1Pos;
        QPointF m_originalScale2Pos;
        QPointF m_originalGroundPos;
        QPointF m_originalFramePos;
        QPointF m_originalAltitudeCtr;
        QPointF m_originalPressureCtr;

        const int m_backZ;
        const int m_scaleZ;
        const int m_labelsZ;
        const int m_groundZ;
        const int m_frameZ;
        const int m_frameTextZ;

        void reset();
        void updateAltitude();
        void updatePressure();
        void updateScale();
        void updateScaleLabels();
    };

    class ASI
    {
    public:

        ASI( QGraphicsScene *scene );
        void init( qreal scaleX, qreal scaleY );
        void update( qreal scaleX, qreal scaleY );
        void setAirspeed( qreal airspeed );
        void setMachNo( qreal machNo );

    private:

        QGraphicsScene *m_scene;

        QGraphicsSvgItem  *m_itemBack;
        QGraphicsSvgItem  *m_itemScale1;
        QGraphicsSvgItem  *m_itemScale2;
        QGraphicsTextItem *m_itemLabel1;
        QGraphicsTextItem *m_itemLabel2;
        QGraphicsTextItem *m_itemLabel3;
        QGraphicsTextItem *m_itemLabel4;
        QGraphicsTextItem *m_itemLabel5;
        QGraphicsTextItem *m_itemLabel6;
        QGraphicsTextItem *m_itemLabel7;
        QGraphicsSvgItem  *m_itemFrame;
        QGraphicsTextItem *m_itemAirspeed;
        QGraphicsTextItem *m_itemMachNo;

        QColor m_frameTextColor;
        QColor m_labelsColor;

        QFont  m_frameTextFont;
        QFont  m_labelsFont;

        qreal m_airspeed;
        qreal m_machNo;

        qreal m_scale1DeltaY_new;
        qreal m_scale1DeltaY_old;
        qreal m_scale2DeltaY_new;
        qreal m_scale2DeltaY_old;
        qreal m_labelsDeltaY_new;
        qreal m_labelsDeltaY_old;

        qreal m_scaleX;
        qreal m_scaleY;

        const qreal m_originalPixPerSpd;
        const qreal m_originalScaleHeight;
        const qreal m_originalLabelsX;
        const qreal m_originalLabel1Y;
        const qreal m_originalLabel2Y;
        const qreal m_originalLabel3Y;
        const qreal m_originalLabel4Y;
        const qreal m_originalLabel5Y;
        const qreal m_originalLabel6Y;
        const qreal m_originalLabel7Y;

        QPointF m_originalBackPos;
        QPointF m_originalScale1Pos;
        QPointF m_originalScale2Pos;
        QPointF m_originalFramePos;
        QPointF m_originalAirspeedCtr;
        QPointF m_originalMachNoCtr;

        const int m_backZ;
        const int m_scaleZ;
        const int m_labelsZ;
        const int m_frameZ;
        const int m_frameTextZ;

        void reset();
        void updateAirspeed();
        void updateScale();
        void updateScaleLabels();
    };

    class HSI
    {
    public:

        HSI( QGraphicsScene *scene );
        void init( qreal scaleX, qreal scaleY );
        void update( qreal scaleX, qreal scaleY );
        void setHeading( qreal heading );

    private:

        QGraphicsScene *m_scene;

        QGraphicsSvgItem  *m_itemBack;
        QGraphicsSvgItem  *m_itemFace;
        QGraphicsSvgItem  *m_itemMarks;
        QGraphicsTextItem *m_itemFrameText;

        QColor m_frameTextColor;

        QFont  m_frameTextFont;

        qreal m_heading;

        qreal m_scaleX;
        qreal m_scaleY;

        QPointF m_originalHsiCtr;
        QPointF m_originalBackPos;
        QPointF m_originalFacePos;
        QPointF m_originalMarksPos;
        QPointF m_originalFrameTextCtr;

        const int m_backZ;
        const int m_faceZ;
        const int m_marksZ;
        const int m_frameTextZ;

        void reset();
        void updateHeading();
    };

    class VSI
    {
    public:

        VSI( QGraphicsScene *scene );
        void init( qreal scaleX, qreal scaleY );
        void update( qreal scaleX, qreal scaleY );
        void setClimbRate( qreal climbRate );

    private:

        QGraphicsScene *m_scene;

        QGraphicsSvgItem  *m_itemScale;
        QGraphicsSvgItem  *m_itemArrow;

        qreal m_climbRate;

        qreal m_arrowDeltaY_new;
        qreal m_arrowDeltaY_old;

        qreal m_scaleX;
        qreal m_scaleY;

        const qreal m_originalMarkeHeight;
        const qreal m_originalPixPerSpd1;
        const qreal m_originalPixPerSpd2;
        const qreal m_originalPixPerSpd4;

        QPointF m_originalScalePos;
        QPointF m_originalArrowPos;

        const int m_scaleZ;
        const int m_arrowZ;

        void reset();
        void updateVSI();
    };

    class ILS
    {
    public:

        ILS( QGraphicsScene *scene );
        void init( qreal scaleX, qreal scaleY );
        void update( qreal scaleX, qreal scaleY );
        void setIdentifier( const QString &ident, bool visible );
        void setDistance( qreal dist, bool visible );

    private:

        QGraphicsScene *m_scene;

        QGraphicsTextItem *m_itemIdentText;
        QGraphicsTextItem *m_itemDistText;

        qreal m_distance;
        QString m_identifier;

        bool m_Dist_Visible;
        bool m_Ident_Visible;

        qreal m_scaleX;
        qreal m_scaleY;

        QPointF m_originalIdentPos;
        QPointF m_originalDistPos;

        const int m_identZ;
        const int m_distZ;

        QColor m_textColor;
        QFont  m_identFont;
        QFont  m_distFont;

        void reset();
        void updateILS();
    };

    QGraphicsScene *m_scene;

    ADI *m_adi;
    ALT *m_alt;
    ASI *m_asi;
    HSI *m_hsi;
    VSI *m_vsi;
    ILS *m_ils;

    QGraphicsSvgItem *m_itemBack;
    QGraphicsSvgItem *m_itemMask;

    qreal m_scaleX;
    qreal m_scaleY;

    const int m_originalHeight;
    const int m_originalWidth;

    const int m_backZ;
    const int m_maskZ;

    void init();
    void reset();
    void updateView();
};

////////////////////////////////////////////////////////////////////////////////

#endif // QFI_PFD_H
