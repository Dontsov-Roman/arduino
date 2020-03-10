#include "Relay.h"

Relay ::Relay(int p, int b)
{
  this->pin = p;
  this->bit = b;
}
void Relay ::toggle(int val)
{
  if ((byte(val) & byte(this->bit)) == this->bit)
  {
    digitalWrite(pin, HIGH);
  }
  else
  {
    digitalWrite(pin, LOW);
  }
}
int Relay::getPin()
{
  return pin;
}

// class Relay : public RelayAbstract
// {
// protected:
//   int pin;
//   int bit;

// public:
//   Relay::Relay(int p, int b)
//   {
//     this->pin = p;
//     this->bit = b;
//   }

//   void toggle(int val)
//   {
//     if ((byte(val) & byte(this->bit)) == this->bit)
//     {
//       digitalWrite(pin, HIGH);
//     }
//     else
//     {
//       digitalWrite(pin, LOW);
//     }
//   }
//   int getPin()
//   {
//     return pin;
//   }
// };
