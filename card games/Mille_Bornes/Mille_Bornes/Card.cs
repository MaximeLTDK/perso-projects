using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Mille_Bornes
{
    public abstract class Card
    {
        public string Name { get; set; }

        public Card(string name)
        {
            this.Name = name;
        }
    }
}
