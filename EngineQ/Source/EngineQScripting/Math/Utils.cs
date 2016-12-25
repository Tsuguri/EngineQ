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

		public static float EPS
		{
			get
			{
				return 0.00001f;
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

		public static float Lerp(float a, float b, float val)
		{
			return (b - a) * val + a;
		}
	}
}
