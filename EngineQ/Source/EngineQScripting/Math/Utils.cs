﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace EngineQ.Math
{
    public static class Utils
    {
		/// <summary>
		/// Math constant: PI ~= 3.14
		/// </summary>
        public static float PI
        {
            get
            {
                return (float)System.Math.PI;
            }
        }

		/// <summary>
		/// Eps to use with float operations, eg. Vectors/Matrix comparison
		/// </summary>
		public static float Eps
		{
			get
			{
				return 0.00001f;
			}
		}

		/// <summary>
		/// Converts angle from degrees do radians.
		/// </summary>
		/// <param name="deg">Angle value in degrees.</param>
		/// <returns>Angle value in radians.</returns>
        public static float DegToRad(float deg)
        {
            return deg / 180.0f * PI;
        }

		/// <summary>
		/// Converts angle from radians to degrees.
		/// </summary>
		/// <param name="rad">Angle value in radians.</param>
		/// <returns>Angle value in degrees.</returns>
        public static float RadToDeg(float rad)
        {
            return rad / PI * 180.0f;
        }

		/// <summary>
		/// Performs linear interpolation between two value.
		/// </summary>
		/// <param name="a">First value.</param>
		/// <param name="b">Second value.</param>
		/// <param name="val">Interpolation parameter. If equal to 0 lerp will return a, if equal to 1 lerp will return b, interpolated value in between</param>
		/// <returns></returns>
		public static float Lerp(float a, float b, float val)
		{
			return (b - a) * val + a;
		}

		/// <summary>
		/// Checks if provided ray is intersecting with <see cref="Sphere"/>. If yes returns distance.
		/// </summary>
		/// <param name="sphere"><see cref="Sphere"/> to intersect</param>
		/// <param name="ray"><see cref="Ray"/> to intersect</param>
		/// <param name="distance">Out parameter which returns distance of intersection</param>
		/// <returns>True if intersection occurs, false otherwise</returns>
		public static bool RaySphereIntersection(Sphere sphere, Ray ray, out float distance)
		{
			Vector3 l = sphere.Center - ray.Origin;
			float tca = Vector3.DotProduct(l, ray.Direction);
			if (tca < 0.0f)
			{
				distance = 0.0f;
				return false;
			}

			float radius2 = sphere.Radius * sphere.Radius;
			float d2 = Vector3.DotProduct(l, l) - tca * tca;
			if (d2 > radius2)
			{
				distance = 0.0f;
				return false;
			}

			float thc = (float)System.Math.Sqrt(radius2 - d2);
			float t0 = tca - thc;
			float t1 = tca + thc;

			if(t0 > t1)
			{
				float tmp = t0;
				t0 = t1;
				t1 = tmp;
			}

			if(t0 < 0.0f)
			{
				t0 = t1;
				if(t0 < 0.0f)
				{
					distance = 0.0f;
					return false;
				}
			}

			distance = t0;
			return true;
		}

		/// <summary>
		/// Checks if provided ray is intersecting with <see cref="Capsule"/>. If yes returns distance.
		/// </summary>
		/// <param name="capsule"><see cref="Capsule"/> to intersect.</param>
		/// <param name="ray"><see cref="Ray"/> to intersect.</param>
		/// <param name="distance">Out parameter which returns distance of intersection</param>
		/// <returns>True if intersection occurs, false otherwise</returns>
		public static bool RayCapsuleIntersection(Capsule capsule, Ray ray, out float distance)
		{
			Vector3 u = capsule.Point2 - capsule.Point1;
			Vector3 v = ray.Direction;
			Vector3 w = capsule.Point1 - ray.Origin;

			float a = Vector3.DotProduct(u, u);         // always >= 0
			float b = Vector3.DotProduct(u, v);
			float c = Vector3.DotProduct(v, v);         // always >= 0
			float d = Vector3.DotProduct(u, w);
			float e = Vector3.DotProduct(v, w);
			float D = a * c - b * b;        // always >= 0
			float sc, sN, sD = D;       // sc = sN / sD, default sD = D >= 0
			float tc, tN, tD = D;       // tc = tN / tD, default tD = D >= 0

			// compute the line parameters of the two closest points
			if (D < Utils.Eps)
			{ // the lines are almost parallel
				sN = 0.0f;         // force using point P0 on segment S1
				sD = 1.0f;         // to prevent possible division by 0.0 later
				tN = e;
				tD = c;
			}
			else
			{                 // get the closest points on the infinite lines
				sN = (b * e - c * d);
				tN = (a * e - b * d);

				if (sN < 0.0f)
				{        // sc < 0 => the s=0 edge is visible
					sN = 0.0f;
					tN = e;
					tD = c;
				}
				else if (sN > sD)
				{  // sc > 1  => the s=1 edge is visible
					sN = sD;
					tN = e + b;
					tD = c;
				}
			}
			
			// finally do the division to get sc and tc
			sc = (System.Math.Abs(sN) < Utils.Eps ? 0.0f : sN / sD);
			tc = (System.Math.Abs(tN) < Utils.Eps ? 0.0f : tN / tD);

			// get the difference of the two closest points
			Vector3 dP = w + (sc * u) - (tc * v);  // =  S1(sc) - S2(tc)

			float capsuleDistance2 = dP.LengthSquared;
			float cpasuleRadius2 = capsule.Radius * capsule.Radius;
			
			if(capsuleDistance2 > cpasuleRadius2)
			{
				distance = 0.0f;
				return false;
			}

			float additionalDistance = (float)System.Math.Sqrt(cpasuleRadius2 - capsuleDistance2);

			if(tc < additionalDistance)
			{
				if(tc < -additionalDistance)
				{
					distance = 0.0f;
					return false;
				}

				distance = tc + additionalDistance;
				return true;
			}

			distance = tc - additionalDistance;
			return true;
		}

		/// <summary>
		/// Checks if provided ray is intersecting with <see cref="Plane"/>. If yes returns distance.
		/// </summary>
		/// <param name="plane"><see cref="Plane"/> to intersect.</param>
		/// <param name="ray"><see cref="Ray"/> to intersect.</param>
		/// <param name="distance">Out parameter which returns distance of intersection.</param>
		/// <returns>True if intersection occurs, false otherwise.</returns>
		public static bool RayPlaneIntersection(Plane plane, Ray ray, out float distance)
		{
			var dot = Vector3.DotProduct(ray.Direction, plane.Normal);

			if(dot < Eps)
			{
				distance = 0.0f;
				return false;
			}
			
			distance = Vector3.DotProduct((plane.Point - ray.Origin), plane.Normal) / dot;
			return true;
		}

		/// <summary>
		/// Computes distance between <see cref="Segment"/>s
		/// </summary>
		/// <param name="segment1">First <see cref="Segment"/>.</param>
		/// <param name="segment2">Second <see cref="Segment"/>.</param>
		/// <returns>Distance between <see cref="Segment"/>s.</returns>
		public static float SegmentToSegmentDistance(Segment segment1, Segment segment2)
		{
			Vector3 u = segment1.Point2 - segment1.Point1;
			Vector3 v = segment2.Point2 - segment2.Point1;
			Vector3 w = segment1.Point1 - segment2.Point1;

			float a = Vector3.DotProduct(u, u);         // always >= 0
			float b = Vector3.DotProduct(u, v);
			float c = Vector3.DotProduct(v, v);         // always >= 0
			float d = Vector3.DotProduct(u, w);
			float e = Vector3.DotProduct(v, w);
			float D = a * c - b * b;        // always >= 0
			float sc, sN, sD = D;       // sc = sN / sD, default sD = D >= 0
			float tc, tN, tD = D;       // tc = tN / tD, default tD = D >= 0

			// compute the line parameters of the two closest points
			if (D < Utils.Eps)
			{ // the lines are almost parallel
				sN = 0.0f;         // force using point P0 on segment S1
				sD = 1.0f;         // to prevent possible division by 0.0 later
				tN = e;
				tD = c;
			}
			else
			{                 // get the closest points on the infinite lines
				sN = (b * e - c * d);
				tN = (a * e - b * d);
				if (sN < 0.0f)
				{        // sc < 0 => the s=0 edge is visible
					sN = 0.0f;
					tN = e;
					tD = c;
				}
				else if (sN > sD)
				{  // sc > 1  => the s=1 edge is visible
					sN = sD;
					tN = e + b;
					tD = c;
				}
			}

			if (tN < 0.0)
			{            // tc < 0 => the t=0 edge is visible
				tN = 0.0f;
				// recompute sc for this edge
				if (-d < 0.0f)
					sN = 0.0f;
				else if (-d > a)
					sN = sD;
				else
				{
					sN = -d;
					sD = a;
				}
			}
			else if (tN > tD)
			{      // tc > 1  => the t=1 edge is visible
				tN = tD;
				// recompute sc for this edge
				if ((-d + b) < 0.0)
					sN = 0;
				else if ((-d + b) > a)
					sN = sD;
				else
				{
					sN = (-d + b);
					sD = a;
				}
			}
			// finally do the division to get sc and tc
			sc = (System.Math.Abs(sN) < Utils.Eps ? 0.0f : sN / sD);
			tc = (System.Math.Abs(tN) < Utils.Eps ? 0.0f : tN / tD);

			// get the difference of the two closest points
			Vector3 dP = w + (sc * u) - (tc * v);  // =  S1(sc) - S2(tc)

			return dP.Length;   // return the closest distance
		}

		/// <summary>
		/// Computes distance between <see cref="Segment"/> and <see cref="Ray"/>.
		/// </summary>
		/// <returns>Distance between <see cref="Segment"/> and <see cref="Ray"/>.</returns>
		public static float SegmentToRayDistance(Segment segment, Ray ray)
		{
			Vector3 u = segment.Point2 - segment.Point1;
			Vector3 v = ray.Direction;
			Vector3 w = segment.Point1 - ray.Origin;

			float a = Vector3.DotProduct(u, u);         // always >= 0
			float b = Vector3.DotProduct(u, v);
			float c = Vector3.DotProduct(v, v);         // always >= 0
			float d = Vector3.DotProduct(u, w);
			float e = Vector3.DotProduct(v, w);
			float D = a * c - b * b;        // always >= 0
			float sc, sN, sD = D;       // sc = sN / sD, default sD = D >= 0
			float tc, tN, tD = D;       // tc = tN / tD, default tD = D >= 0

			// compute the line parameters of the two closest points
			if (D < Utils.Eps)
			{ // the lines are almost parallel
				sN = 0.0f;         // force using point P0 on segment S1
				sD = 1.0f;         // to prevent possible division by 0.0 later
				tN = e;
				tD = c;
			}
			else
			{                 // get the closest points on the infinite lines
				sN = (b * e - c * d);
				tN = (a * e - b * d);

				if (sN < 0.0f)
				{        // sc < 0 => the s=0 edge is visible
					sN = 0.0f;
					tN = e;
					tD = c;
				}
				else if (sN > sD)
				{  // sc > 1  => the s=1 edge is visible
					sN = sD;
					tN = e + b;
					tD = c;
				}
			}

			if (tN < 0.0)
			{            // tc < 0 => the t=0 edge is visible
				tN = 0.0f;
				// recompute sc for this edge
				if (-d < 0.0f)
					sN = 0.0f;
				else if (-d > a)
					sN = sD;
				else
				{
					sN = -d;
					sD = a;
				}
			}

			// finally do the division to get sc and tc
			sc = (System.Math.Abs(sN) < Utils.Eps ? 0.0f : sN / sD);
			tc = (System.Math.Abs(tN) < Utils.Eps ? 0.0f : tN / tD);

			// get the difference of the two closest points
			Vector3 dP = w + (sc * u) - (tc * v);  // =  S1(sc) - S2(tc)

			return dP.Length;   // return the closest distance
		}

		/// <summary>
		/// Computes distance between two lines.
		/// </summary>
		/// <param name="line1">First line.</param>
		/// <param name="line2">Second line.</param>
		/// <returns>Computed distance.</returns>
		public static float LineToLineDistance(Segment line1, Segment line2)
		{
			Vector3 u = line1.Point2 - line1.Point1;
			Vector3 v = line2.Point2 - line2.Point1;
			Vector3 w = line1.Point1 - line2.Point1;

			float a = Vector3.DotProduct(u, u);         // always >= 0
			float b = Vector3.DotProduct(u, v);
			float c = Vector3.DotProduct(v, v);         // always >= 0
			float d = Vector3.DotProduct(u, w);
			float e = Vector3.DotProduct(v, w);
			float D = a * c - b * b;        // always >= 0
			float sc, tc;

			// compute the line parameters of the two closest points
			if (D < Utils.Eps)
			{          // the lines are almost parallel
				sc = 0.0f;
				tc = (b > c ? d / b : e / c);    // use the largest denominator
			}
			else
			{
				sc = (b * e - c * d) / D;
				tc = (a * e - b * d) / D;
			}

			// get the difference of the two closest points
			Vector3 dP = w + (sc * u) - (tc * v);  // =  L1(sc) - L2(tc)

			return dP.Length;   // return the closest distance
		}
	}
}
