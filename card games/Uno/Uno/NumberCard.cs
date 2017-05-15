using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Uno
{
    public class NumberCard : Card
    {
        private int number;

        public int Number
        {
            get
            {
                return this.number;
            }
            set
            {
                try
                {
                    if (value >= 0 && value <= 9)
                        this.number = value;
                    else
                        throw new Exception();
                }
                catch (Exception)
                {
                    Console.Error.WriteLine("Non-valid number card");
                }
            }
        }

        public NumberCard(string name, ColorType color, int number) : base(name, color)
        {
            this.Number = number;
        }
    }
}
