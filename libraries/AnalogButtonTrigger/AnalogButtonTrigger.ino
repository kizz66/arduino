class AnalogButtonTrigger {
  protected:
    int buttonTrigger = LOW,
        oldButton = LOW ,
        button = LOW,
        input = 0;
  public:
    AnalogButtonTrigger(int input) {
      this->input = input;
    }

    int check(void) {
      this->button = analogRead(this->input) > 0 ? HIGH : LOW;
      if (this->button != this->oldButton) {
        this->oldButton = this->button;
        if (this->button == LOW) {
          if (this->buttonTrigger == LOW) {
            this->buttonTrigger = HIGH;
          } else {
            this->buttonTrigger = LOW;
          }
        }
      }
      return this->buttonTrigger;
    }
};
