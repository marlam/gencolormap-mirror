/*
 * Copyright (C) 2015, 2016, 2017, 2018, 2019, 2020
 * Computer Graphics Group, University of Siegen
 * Written by Martin Lambers <martin.lambers@uni-siegen.de>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#ifndef COLORMAPWIDGETS_HPP
#define COLORMAPWIDGETS_HPP

#include <QVector>
#include <QWidget>

class QSpinBox;
class QSlider;
class QDoubleSpinBox;
class QPushButton;
class QListWidget;

// Internal helper class for a slider/spinbox combination
class ColorMapCombinedSliderSpinBox : public QObject
{
Q_OBJECT

private:
    bool _update_lock;

public:
    float minval, maxval, step;
    QSlider* slider;
    QDoubleSpinBox* spinbox;

    ColorMapCombinedSliderSpinBox(float minval, float maxval, float step);
    float value() const;
    void setValue(float v);

private slots:
    void sliderChanged();
    void spinboxChanged();

signals:
    void valueChanged(float);
};

/* The ColorMapWidget interface, implemented by all color map method widgets */
class ColorMapWidget : public QWidget
{
Q_OBJECT

public:
    ColorMapWidget();
    ~ColorMapWidget();

    /* Reset all values to their method-specific defaults */
    virtual void reset() = 0;

    /* Get the color map corresponding to the current values as a vector of colors.
     * Also return the number of clipped colors unless 'clipped' is NULL. */
    virtual QVector<unsigned char> colorMap(int* clipped = NULL) const = 0;

    /* Transform a color map to an image of the specified size. If width or
     * height is zero, then it will be set to the number of colors in the
     * color map. */
    static QImage colorMapImage(const QVector<unsigned char>& colormap, int width, int height);

    /* Get a rich text string containing the relevant literature reference for this method */
    virtual QString reference() const = 0;

signals:
    void colorMapChanged();
};

class ColorMapBrewerSequentialWidget : public ColorMapWidget
{
Q_OBJECT
private:
    bool _update_lock;
    QSpinBox* _n_spinbox;
    ColorMapCombinedSliderSpinBox* _hue_changer;
    ColorMapCombinedSliderSpinBox* _warmth_changer;
    ColorMapCombinedSliderSpinBox* _contrast_changer;
    ColorMapCombinedSliderSpinBox* _saturation_changer;
    ColorMapCombinedSliderSpinBox* _brightness_changer;
private slots:
    void update();

public:
    ColorMapBrewerSequentialWidget();
    ~ColorMapBrewerSequentialWidget();

    void reset() override;
    QVector<unsigned char> colorMap(int* clipped = NULL) const override;
    QString reference() const override;
    void parameters(int& n, float& hue,
            float& contrast, float& saturation, float& brightness, float& warmth) const;
};

class ColorMapBrewerDivergingWidget : public ColorMapWidget
{
Q_OBJECT
private:
    bool _update_lock;
    QSpinBox* _n_spinbox;
    ColorMapCombinedSliderSpinBox* _hue_changer;
    ColorMapCombinedSliderSpinBox* _divergence_changer;
    ColorMapCombinedSliderSpinBox* _warmth_changer;
    ColorMapCombinedSliderSpinBox* _contrast_changer;
    ColorMapCombinedSliderSpinBox* _saturation_changer;
    ColorMapCombinedSliderSpinBox* _brightness_changer;
private slots:
    void update();

public:
    ColorMapBrewerDivergingWidget();
    ~ColorMapBrewerDivergingWidget();

    void reset() override;
    QVector<unsigned char> colorMap(int* clipped = NULL) const override;
    QString reference() const override;
    void parameters(int& n, float& hue, float& divergence,
            float& contrast, float& saturation, float& brightness, float& warmth) const;
};

class ColorMapBrewerQualitativeWidget : public ColorMapWidget
{
Q_OBJECT
private:
    bool _update_lock;
    QSpinBox* _n_spinbox;
    ColorMapCombinedSliderSpinBox* _hue_changer;
    ColorMapCombinedSliderSpinBox* _divergence_changer;
    ColorMapCombinedSliderSpinBox* _contrast_changer;
    ColorMapCombinedSliderSpinBox* _saturation_changer;
    ColorMapCombinedSliderSpinBox* _brightness_changer;
private slots:
    void update();

public:
    ColorMapBrewerQualitativeWidget();
    ~ColorMapBrewerQualitativeWidget();

    void reset() override;
    QVector<unsigned char> colorMap(int* clipped = NULL) const override;
    QString reference() const override;
    void parameters(int& n, float& hue, float& divergence,
            float& contrast, float& saturation, float& brightness) const;
};

class ColorMapPUSequentialLightnessWidget : public ColorMapWidget
{
Q_OBJECT
private:
    bool _update_lock;
    QSpinBox* _n_spinbox;
    ColorMapCombinedSliderSpinBox* _lightness_range_changer;
    ColorMapCombinedSliderSpinBox* _saturation_range_changer;
    ColorMapCombinedSliderSpinBox* _saturation_changer;
    ColorMapCombinedSliderSpinBox* _hue_changer;
private slots:
    void update();

public:
    ColorMapPUSequentialLightnessWidget();
    ~ColorMapPUSequentialLightnessWidget();

    void reset() override;
    QVector<unsigned char> colorMap(int* clipped = NULL) const override;
    QString reference() const override;
    void parameters(int& n, float& lightness_range, float& saturation_range, float& saturation, float& hue) const;
};

class ColorMapPUSequentialSaturationWidget : public ColorMapWidget
{
Q_OBJECT
private:
    bool _update_lock;
    QSpinBox* _n_spinbox;
    ColorMapCombinedSliderSpinBox* _saturation_range_changer;
    ColorMapCombinedSliderSpinBox* _lightness_changer;
    ColorMapCombinedSliderSpinBox* _saturation_changer;
    ColorMapCombinedSliderSpinBox* _hue_changer;
private slots:
    void update();

public:
    ColorMapPUSequentialSaturationWidget();
    ~ColorMapPUSequentialSaturationWidget();

    void reset() override;
    QVector<unsigned char> colorMap(int* clipped = NULL) const override;
    QString reference() const override;
    void parameters(int& n, float& saturation_range, float& lightness, float& saturation, float& hue) const;
};

class ColorMapPUSequentialRainbowWidget : public ColorMapWidget
{
Q_OBJECT
private:
    bool _update_lock;
    QSpinBox* _n_spinbox;
    ColorMapCombinedSliderSpinBox* _lightness_range_changer;
    ColorMapCombinedSliderSpinBox* _saturation_range_changer;
    ColorMapCombinedSliderSpinBox* _hue_changer;
    ColorMapCombinedSliderSpinBox* _rotations_changer;
    ColorMapCombinedSliderSpinBox* _saturation_changer;
private slots:
    void update();

public:
    ColorMapPUSequentialRainbowWidget();
    ~ColorMapPUSequentialRainbowWidget();

    void reset() override;
    QVector<unsigned char> colorMap(int* clipped = NULL) const override;
    QString reference() const override;
    void parameters(int& n, float& lightness_range, float& saturation_range, float& hue, float& rotations, float& saturation) const;
};

class ColorMapPUSequentialBlackBodyWidget : public ColorMapWidget
{
Q_OBJECT
private:
    bool _update_lock;
    QSpinBox* _n_spinbox;
    ColorMapCombinedSliderSpinBox* _temperature_changer;
    ColorMapCombinedSliderSpinBox* _temperature_range_changer;
    ColorMapCombinedSliderSpinBox* _lightness_range_changer;
    ColorMapCombinedSliderSpinBox* _saturation_range_changer;
    ColorMapCombinedSliderSpinBox* _saturation_changer;
private slots:
    void update();

public:
    ColorMapPUSequentialBlackBodyWidget();
    ~ColorMapPUSequentialBlackBodyWidget();

    void reset() override;
    QVector<unsigned char> colorMap(int* clipped = NULL) const override;
    QString reference() const override;
    void parameters(int& n, float& temperature, float& temperature_range, float& lightness_range, float& saturation_range, float& saturation) const;
};

class ColorMapPUSequentialMultiHueWidget : public ColorMapWidget
{
Q_OBJECT
private:
    bool _update_lock;
    QSpinBox* _n_spinbox;
    QListWidget* _hue_list_widget;
    QColor _hue_button_color;
    QPushButton* _hue_button;
    QDoubleSpinBox* _pos_spinbox;
    ColorMapCombinedSliderSpinBox* _lightness_range_changer;
    ColorMapCombinedSliderSpinBox* _saturation_range_changer;
    ColorMapCombinedSliderSpinBox* _saturation_changer;
    void updateHueButton();
private slots:
    void update();
    void hueButtonClicked();
    void colorSelected(const QColor& color);
    void addHue();
    void removeHue();

public:
    ColorMapPUSequentialMultiHueWidget();
    ~ColorMapPUSequentialMultiHueWidget();

    void reset() override;
    QVector<unsigned char> colorMap(int* clipped = NULL) const override;
    QString reference() const override;
    void parameters(int& n,
            float& lr, float& sr, float& s,
            QVector<float>& hue_values, QVector<float>& hue_positions) const;
};

class ColorMapPUDivergingLightnessWidget : public ColorMapWidget
{
Q_OBJECT
private:
    bool _update_lock;
    QSpinBox* _n_spinbox;
    ColorMapCombinedSliderSpinBox* _lightness_range_changer;
    ColorMapCombinedSliderSpinBox* _saturation_range_changer;
    ColorMapCombinedSliderSpinBox* _saturation_changer;
    ColorMapCombinedSliderSpinBox* _hue_changer;
    ColorMapCombinedSliderSpinBox* _divergence_changer;
private slots:
    void update();

public:
    ColorMapPUDivergingLightnessWidget();
    ~ColorMapPUDivergingLightnessWidget();

    void reset() override;
    QVector<unsigned char> colorMap(int* clipped = NULL) const override;
    QString reference() const override;
    void parameters(int& n, float& lightness_range, float& saturation_range, float& saturation, float& hue, float& divergence) const;
};

class ColorMapPUDivergingSaturationWidget : public ColorMapWidget
{
Q_OBJECT
private:
    bool _update_lock;
    QSpinBox* _n_spinbox;
    ColorMapCombinedSliderSpinBox* _saturation_range_changer;
    ColorMapCombinedSliderSpinBox* _lightness_changer;
    ColorMapCombinedSliderSpinBox* _saturation_changer;
    ColorMapCombinedSliderSpinBox* _hue_changer;
    ColorMapCombinedSliderSpinBox* _divergence_changer;
private slots:
    void update();

public:
    ColorMapPUDivergingSaturationWidget();
    ~ColorMapPUDivergingSaturationWidget();

    void reset() override;
    QVector<unsigned char> colorMap(int* clipped = NULL) const override;
    QString reference() const override;
    void parameters(int& n, float& saturation_range, float& lightness, float& saturation, float& hue, float& divergence) const;
};

class ColorMapPUQualitativeHueWidget : public ColorMapWidget
{
Q_OBJECT
private:
    bool _update_lock;
    QSpinBox* _n_spinbox;
    ColorMapCombinedSliderSpinBox* _hue_changer;
    ColorMapCombinedSliderSpinBox* _divergence_changer;
    ColorMapCombinedSliderSpinBox* _lightness_changer;
    ColorMapCombinedSliderSpinBox* _saturation_changer;
private slots:
    void update();

public:
    ColorMapPUQualitativeHueWidget();
    ~ColorMapPUQualitativeHueWidget();

    void reset() override;
    QVector<unsigned char> colorMap(int* clipped = NULL) const override;
    QString reference() const override;
    void parameters(int& n, float& hue, float& divergence, float& lightness, float& saturation) const;
};

class ColorMapCubeHelixWidget : public ColorMapWidget
{
Q_OBJECT
private:
    bool _update_lock;
    QSpinBox* _n_spinbox;
    ColorMapCombinedSliderSpinBox* _hue_changer;
    ColorMapCombinedSliderSpinBox* _rotations_changer;
    ColorMapCombinedSliderSpinBox* _saturation_changer;
    ColorMapCombinedSliderSpinBox* _gamma_changer;
private slots:
    void update();

public:
    ColorMapCubeHelixWidget();
    ~ColorMapCubeHelixWidget();

    void reset() override;
    QVector<unsigned char> colorMap(int* clipped = NULL) const override;
    QString reference() const override;
    void parameters(int& n, float& hue, float& rotations,
            float& saturation, float& gamma) const;
};

class ColorMapMorelandWidget : public ColorMapWidget
{
Q_OBJECT
private:
    bool _update_lock;
    QSpinBox* _n_spinbox;
    QPushButton* _color0_button;
    QPushButton* _color1_button;
private slots:
    void chooseColor0();
    void color0Selected(const QColor& color0);
    void chooseColor1();
    void color1Selected(const QColor& color1);
    void update();

public:
    ColorMapMorelandWidget();
    ~ColorMapMorelandWidget();

    void reset() override;
    QVector<unsigned char> colorMap(int* clipped = NULL) const override;
    QString reference() const override;
    void parameters(int& n,
            unsigned char& r0, unsigned char& g0, unsigned char& b0,
            unsigned char& r1, unsigned char& g1, unsigned char& b1) const;
};

class ColorMapMcNamesWidget : public ColorMapWidget
{
Q_OBJECT
private:
    bool _update_lock;
    QSpinBox* _n_spinbox;
    ColorMapCombinedSliderSpinBox* _periods_changer;
private slots:
    void update();

public:
    ColorMapMcNamesWidget();
    ~ColorMapMcNamesWidget();

    void reset() override;
    QVector<unsigned char> colorMap(int* clipped = NULL) const override;
    QString reference() const override;
    void parameters(int& n, float& p) const;
};

#endif
