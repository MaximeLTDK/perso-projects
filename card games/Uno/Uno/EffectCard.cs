using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Uno
{
    public class EffectCard : Card
    {
        public enum EffectType { Skip, Reverse, Wild, Draw_Two, Wild_Draw_Four }

        public EffectType Effect { get; set; }

        public EffectCard(string name, EffectType effect) : base(name)
        {
            try
            {
                if (effect == EffectType.Wild || effect == EffectType.Wild_Draw_Four)
                {
                    this.Color = ColorType.Wild;
                    this.Effect = effect;
                }
                else
                {
                    throw new Exception();
                }
            }
            catch (Exception)
            {
                Console.Error.WriteLine("Non-wild effect card must get a color");
            }
        }

        public EffectCard(string name, ColorType color, EffectType effect) : base(name, color)
        {
            try
            {
                if (effect == EffectType.Wild || effect == EffectType.Wild_Draw_Four)
                {
                    if (color == ColorType.Wild)
                        this.Effect = effect;
                    else
                        throw new Exception();
                }
                else
                {
                    if (color != ColorType.Wild)
                        this.Effect = effect;
                    else
                        throw new Exception();
                }
            }
            catch (Exception)
            {
                Console.Error.WriteLine("Wild effect card must get wild color");
            }
        }
    }
}
