class MapEncoder: public Encoder {
  protected:

    int _button;
    long _value;
    long _prevPosition;
    int _minValue;
    int _maxValue;
    int _scale;
    int _initPos;

  public:
    int pinA = 3;
    int pinB = 4;
    
    MapEncoder(int a, int b): Encoder(a, b) {
      this->pinA = a;
      this->pinB = b;
 
      this->_prevPosition = this->read();
      this->setScale();
    };

    void setScale(int minValue = -180, int maxValue = 180, int initPos = 0, int scale = 1)
    {
      this->_value = initPos;
      this->_minValue = minValue;
      this->_maxValue = maxValue;
      this->_scale =  scale;
      this->_initPos =  initPos;
    }

    long getValue() {
      int pos = this->read();
      int delta = pos - this->_prevPosition;
      this->_prevPosition = pos;

      this->_value += delta;

      if (this->_value < this->_minValue) {
        this->_value = this->_minValue;
      }

      if (this->_value > this->_maxValue) {
        this->_value = this->_maxValue;
      }
      
      return this->_value;
    }
};
