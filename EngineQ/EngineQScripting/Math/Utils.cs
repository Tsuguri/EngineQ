using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EngineQ.Math
{
    public static class Utils
    {
        public static float PI
        {
            get
            {
                return (float)System.Math.PI;
            }
        }

        public static float DegToRad(float deg)
        {
            return deg / 180.0f * PI;
        }

        public static float RadToDeg(float rad)
        {
            return rad / PI * 180.0f;
        }
    }
}
