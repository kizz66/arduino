/*
   Преобразование значений к шкале
  ScaleValue someValue = new ScaleValue(0, 1023, 0, 180);
  int scaleValue = someValue.scaleValue(555);
*/
class ScaleValue {

  protected:

    int _value;
    int _minValue;
    int _maxValue;
    int _minScale;
    int _maxScale;

  public:

    ScaleValue(int minVal = 0, int maxVal = 1023, int minScale = 0, int maxScale = 100)
    {
      this->setMinValue(minVal);
      this->setMaxValue(maxVal);
      this->_minScale =  minScale;
      this->_maxScale =  maxScale;
    }

    void setValue(float value) {
      this->_value = value;
    }

    void setMinValue(int minValue) {
      this->_minValue = minValue;
    }

    void setMaxValue(int maxValue) {
      this->_maxValue = maxValue;
    }

    void setMinScale(int minScale) {
      this->_minScale = minScale;
    }

    void setMaxScale(int maxScale) {
      this->_maxScale = maxScale;
    }

    int getValue(void) {
      return this->_value;
    }

    int getMinValue(void) {
      return this->_minValue;
    }

    int getMaxValue(void) {
      return this->_maxValue;
    }

    int getMinScale(void) {
      return this->_minScale;
    }

    int getMaxScale(void) {
      return this->_maxScale;
    }
    /*
      Возвращает значение приведенное к шкале
    */
    int scaleValue(float value) {
      this->setValue(value);
      return map(value, this->getMinValue(), this->getMaxValue(), this->getMinScale(), this->getMaxScale());
    }
};
