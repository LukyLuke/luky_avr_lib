#ifndef LZU_STEPPER 
#define LZU_STEPPER

#include <cstdint>

#define STEPPER_NUM_STEPS 8

namespace LukyLuke {
  namespace avr {
    namespace libraries {
      
      class Stepper {
      public:
        enum DIRECTION { LEFT, RIGHT };
        
        Stepper(const uint8_t pin1, const uint8_t pin2, const uint8_t pin3, const uint8_t pin4);
        void move(const int8_t steps, const uint8_t speed);
        void step(DIRECTION direction);
        
      private:
        const uint8_t p1;
        const uint8_t p2;
        const uint8_t p3;
        const uint8_t p4;
        uint8_t position;
        
        void shutdown();
        void to_position(const uint8_t pos);
        
        byte positions[][] = {
          {0, 0, 0, 1},
          {0, 0, 1, 1},
          {0, 0, 1, 0},
          {0, 1, 1, 0},
          {0, 1, 0, 0},
          {1, 1, 0, 0},
          {1, 0, 0, 0},
          {1, 0, 0, 1}
        };
      }
      
      
    }
  }
}

#endif // LZU_STEPPER
