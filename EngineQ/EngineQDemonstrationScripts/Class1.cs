﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using EngineQ;
using EngineQ.Math;


namespace QScripts
{
    public class CameraMoveClass : Script
    {
	    public override void Update()
	    {
		    base.Update();

		    var p = Entity.Transform.Position;
		    p.Y = (float)Math.Sin(1);
	    }
    }
}
