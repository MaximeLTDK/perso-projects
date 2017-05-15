using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Uno
{
    class Program
    {
        static void Main(string[] args)
        {
            NumberCard nc = new NumberCard("1 green card", Card.ColorType.Green, 10);
            EffectCard ec1 = new EffectCard("Shift card", EffectCard.EffectType.Reverse);
            EffectCard ec2 = new EffectCard("Shift red card", Card.ColorType.Red, EffectCard.EffectType.Reverse);
            EffectCard ec3 = new EffectCard("Wild wild card", Card.ColorType.Wild, EffectCard.EffectType.Wild);
            EffectCard ec4 = new EffectCard("Wild Draw Four card", EffectCard.EffectType.Wild_Draw_Four);
            EffectCard ec5 = new EffectCard("Wild Draw Four blue card", Card.ColorType.Green, EffectCard.EffectType.Wild_Draw_Four);
        }
    }
}
