using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Uno
{
    public abstract class Card
    {
        public enum ColorType { Red, Blue, Green, Yellow, Wild }

        public string Name { get; set; }
        public ColorType Color { get; set; }

        public Card(string name)
        {
            this.Name = name;
            this.Color = ColorType.Wild;
        }

        public Card(string name, ColorType color)
        {
            this.Name = name;
            this.Color = color;
        }
    }
}
