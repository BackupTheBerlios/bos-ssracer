xof 0303txt 0032
template XSkinMeshHeader {
 <3cf169ce-ff7c-44ab-93c0-f78f62d172e2>
 WORD nMaxSkinWeightsPerVertex;
 WORD nMaxSkinWeightsPerFace;
 WORD nBones;
}

template VertexDuplicationIndices {
 <b8d65549-d7c9-4995-89cf-53a9a8b031e3>
 DWORD nIndices;
 DWORD nOriginalVertices;
 array DWORD indices[nIndices];
}

template SkinWeights {
 <6f0d123b-bad2-4167-a0d0-80224f25fabb>
 STRING transformNodeName;
 DWORD nWeights;
 array DWORD vertexIndices[nWeights];
 array FLOAT weights[nWeights];
 Matrix4x4 matrixOffset;
}


Frame SCENE_ROOT {
 

 FrameTransformMatrix {
  1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
 }

 Frame groundPlane_transform {
  

  FrameTransformMatrix {
   2355.000000,0.000000,0.000000,0.000000,0.000000,0.000000,2355.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
  }
 }

 Frame persp {
  

  FrameTransformMatrix {
   0.707107,0.000000,-0.707107,0.000000,-0.331295,0.883452,-0.331295,0.000000,0.624695,0.468521,0.624695,0.000000,5652.000000,4239.000000,5652.000000,1.000000;;
  }
 }

 Frame top {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,100.000000,0.000000,1.000000;;
  }
 }

 Frame front {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,100.000000,1.000000;;
  }
 }

 Frame side {
  

  FrameTransformMatrix {
   0.000000,0.000000,-1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,100.000000,0.000000,0.000000,1.000000;;
  }
 }

 Frame polySurface1 {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
  }

  Mesh polySurfaceShape1 {
   122;
   -131.232529;0.000000;227.125870;,
   -78.739517;0.000000;136.275528;,
   -80.718872;0.000000;135.131866;,
   -133.211868;0.000000;225.982208;,
   -82.698219;0.000000;133.988205;,
   -135.191238;0.000000;224.838547;,
   -83.687897;0.000000;133.416382;,
   -136.180893;0.000000;224.266724;,
   -83.687897;0.400000;133.416382;,
   -136.180893;0.400000;224.266724;,
   -85.664322;0.400000;132.274399;,
   -138.157333;0.400000;223.124741;,
   -26.246506;0.000000;45.425175;,
   -28.225857;0.000000;44.281513;,
   -30.205210;0.000000;43.137852;,
   -31.194885;0.000000;42.566021;,
   -31.194885;0.400000;42.566021;,
   -33.171310;0.400000;41.424049;,
   26.246506;0.000000;-45.425175;,
   24.267155;0.000000;-46.568840;,
   22.287802;0.000000;-47.712502;,
   21.298126;0.000000;-48.284332;,
   21.298126;0.400000;-48.284332;,
   19.321701;0.400000;-49.426304;,
   78.739517;0.000000;-136.275528;,
   76.760162;0.000000;-137.419189;,
   74.780815;0.000000;-138.562866;,
   73.791138;0.000000;-139.134689;,
   73.791138;0.400000;-139.134689;,
   71.814713;0.400000;-140.276657;,
   131.232529;0.000000;-227.125870;,
   129.253174;0.000000;-228.269531;,
   127.273827;0.000000;-229.413193;,
   126.284149;0.000000;-229.985031;,
   126.284149;0.400000;-229.985031;,
   124.307724;0.400000;-231.126999;,
   -129.253174;0.000000;228.269531;,
   -76.760162;0.000000;137.419189;,
   -127.273827;0.000000;229.413193;,
   -74.780815;0.000000;138.562866;,
   -126.284149;0.000000;229.985031;,
   -73.791138;0.000000;139.134689;,
   -126.284149;0.400000;229.985031;,
   -73.791138;0.400000;139.134689;,
   -124.307724;0.400000;231.126999;,
   -71.814713;0.400000;140.276657;,
   -24.267155;0.000000;46.568840;,
   -22.287802;0.000000;47.712502;,
   -21.298126;0.000000;48.284332;,
   -21.298126;0.400000;48.284332;,
   -19.321701;0.400000;49.426304;,
   28.225857;0.000000;-44.281513;,
   30.205210;0.000000;-43.137852;,
   31.194885;0.000000;-42.566021;,
   31.194885;0.400000;-42.566021;,
   33.171310;0.400000;-41.424049;,
   80.718872;0.000000;-135.131866;,
   82.698219;0.000000;-133.988205;,
   83.687897;0.000000;-133.416382;,
   83.687897;0.400000;-133.416382;,
   85.664322;0.400000;-132.274399;,
   133.211868;0.000000;-225.982208;,
   135.191238;0.000000;-224.838547;,
   136.180893;0.000000;-224.266724;,
   136.180893;0.400000;-224.266724;,
   138.157333;0.400000;-223.124741;,
   -136.180893;0.000000;224.266724;,
   -83.687897;0.000000;133.416382;,
   -136.180893;0.400000;224.266724;,
   -83.687897;0.400000;133.416382;,
   -83.687897;0.000000;133.416382;,
   -31.194885;0.000000;42.566021;,
   -83.687897;0.400000;133.416382;,
   -83.687897;0.400000;133.416382;,
   -31.194885;0.400000;42.566021;,
   -85.664322;0.400000;132.274399;,
   -31.194885;0.000000;42.566021;,
   21.298126;0.000000;-48.284332;,
   -31.194885;0.400000;42.566021;,
   -31.194885;0.400000;42.566021;,
   21.298126;0.400000;-48.284332;,
   -33.171310;0.400000;41.424049;,
   21.298126;0.000000;-48.284332;,
   73.791138;0.000000;-139.134689;,
   21.298126;0.400000;-48.284332;,
   21.298126;0.400000;-48.284332;,
   73.791138;0.400000;-139.134689;,
   19.321701;0.400000;-49.426304;,
   73.791138;0.000000;-139.134689;,
   126.284149;0.000000;-229.985031;,
   73.791138;0.400000;-139.134689;,
   73.791138;0.400000;-139.134689;,
   126.284149;0.400000;-229.985031;,
   71.814713;0.400000;-140.276657;,
   -126.284149;0.000000;229.985031;,
   -73.791138;0.000000;139.134689;,
   -126.284149;0.400000;229.985031;,
   -73.791138;0.400000;139.134689;,
   -73.791138;0.000000;139.134689;,
   -73.791138;0.400000;139.134689;,
   -21.298126;0.000000;48.284332;,
   -73.791138;0.400000;139.134689;,
   -71.814713;0.400000;140.276657;,
   -21.298126;0.400000;48.284332;,
   -21.298126;0.000000;48.284332;,
   -21.298126;0.400000;48.284332;,
   31.194885;0.000000;-42.566021;,
   -21.298126;0.400000;48.284332;,
   -19.321701;0.400000;49.426304;,
   31.194885;0.400000;-42.566021;,
   31.194885;0.000000;-42.566021;,
   31.194885;0.400000;-42.566021;,
   83.687897;0.000000;-133.416382;,
   31.194885;0.400000;-42.566021;,
   33.171310;0.400000;-41.424049;,
   83.687897;0.400000;-133.416382;,
   83.687897;0.000000;-133.416382;,
   83.687897;0.400000;-133.416382;,
   136.180893;0.000000;-224.266724;,
   83.687897;0.400000;-133.416382;,
   85.664322;0.400000;-132.274399;,
   136.180893;0.400000;-224.266724;;
   50;
   4;3,2,1,0;,
   4;5,4,2,3;,
   4;7,6,4,5;,
   4;9,8,67,66;,
   4;11,10,69,68;,
   4;2,13,12,1;,
   4;4,14,13,2;,
   4;6,15,14,4;,
   4;72,16,71,70;,
   4;75,17,74,73;,
   4;13,19,18,12;,
   4;14,20,19,13;,
   4;15,21,20,14;,
   4;78,22,77,76;,
   4;81,23,80,79;,
   4;19,25,24,18;,
   4;20,26,25,19;,
   4;21,27,26,20;,
   4;84,28,83,82;,
   4;87,29,86,85;,
   4;25,31,30,24;,
   4;26,32,31,25;,
   4;27,33,32,26;,
   4;90,34,89,88;,
   4;93,35,92,91;,
   4;1,37,36,0;,
   4;37,39,38,36;,
   4;39,41,40,38;,
   4;95,43,42,94;,
   4;97,45,44,96;,
   4;12,46,37,1;,
   4;46,47,39,37;,
   4;47,48,41,39;,
   4;100,49,99,98;,
   4;103,50,102,101;,
   4;18,51,46,12;,
   4;51,52,47,46;,
   4;52,53,48,47;,
   4;106,54,105,104;,
   4;109,55,108,107;,
   4;24,56,51,18;,
   4;56,57,52,51;,
   4;57,58,53,52;,
   4;112,59,111,110;,
   4;115,60,114,113;,
   4;30,61,56,24;,
   4;61,62,57,56;,
   4;62,63,58,57;,
   4;118,64,117,116;,
   4;121,65,120,119;;

   MeshNormals {
    21;
    -0.865858;-0.000005;-0.500290;,
    -0.865858;0.000000;-0.500290;,
    -0.865858;0.000000;-0.500290;,
    -0.865858;0.000004;-0.500290;,
    -0.865858;-0.000000;-0.500290;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.865858;0.000000;0.500290;,
    0.865858;-0.000004;0.500290;,
    0.865858;-0.000000;0.500290;,
    0.865858;-0.000000;0.500290;,
    0.865858;0.000005;0.500290;;
    50;
    4;14,14,14,14;,
    4;14,14,14,14;,
    4;14,14,14,14;,
    4;20,20,20,20;,
    4;13,13,13,13;,
    4;14,14,14,14;,
    4;14,14,14,14;,
    4;14,14,14,14;,
    4;17,17,17,17;,
    4;8,8,8,8;,
    4;14,14,14,14;,
    4;14,14,14,14;,
    4;14,14,14,14;,
    4;18,18,18,18;,
    4;7,7,7,7;,
    4;14,14,14,14;,
    4;14,14,14,14;,
    4;14,14,14,14;,
    4;19,19,19,19;,
    4;6,6,6,6;,
    4;14,14,14,14;,
    4;14,14,14,14;,
    4;14,14,14,14;,
    4;16,16,16,16;,
    4;5,5,5,5;,
    4;14,14,14,14;,
    4;14,14,14,14;,
    4;14,14,14,14;,
    4;4,4,4,4;,
    4;9,9,9,9;,
    4;14,14,14,14;,
    4;14,14,14,14;,
    4;14,14,14,14;,
    4;1,1,1,1;,
    4;10,10,10,10;,
    4;14,14,14,14;,
    4;14,14,14,14;,
    4;14,14,14,14;,
    4;2,2,2,2;,
    4;11,11,11,11;,
    4;14,14,14,14;,
    4;14,14,14,14;,
    4;14,14,14,14;,
    4;3,3,3,3;,
    4;12,12,12,12;,
    4;14,14,14,14;,
    4;14,14,14,14;,
    4;14,14,14,14;,
    4;0,0,0,0;,
    4;15,15,15,15;;
   }

   MeshTextureCoords {
    122;
    0.500000;11.346992;,
    0.500000;7.008183;,
    0.387386;7.008183;,
    0.387386;11.346992;,
    0.274772;7.008183;,
    0.274772;11.346992;,
    0.218465;7.008183;,
    0.218465;11.346992;,
    0.164043;7.008183;,
    0.164043;11.346992;,
    0.001709;7.008183;,
    0.001709;11.346992;,
    0.500000;2.669394;,
    0.387386;2.669394;,
    0.274772;2.669394;,
    0.218465;2.669394;,
    0.164043;2.669394;,
    0.001709;2.669394;,
    0.500000;-1.669394;,
    0.387386;-1.669394;,
    0.274772;-1.669394;,
    0.218465;-1.669394;,
    0.164043;-1.669394;,
    0.001709;-1.669394;,
    0.500000;-6.008182;,
    0.387386;-6.008182;,
    0.274772;-6.008182;,
    0.218465;-6.008182;,
    0.164043;-6.008182;,
    0.001709;-6.008182;,
    0.500000;-10.346991;,
    0.387386;-10.346991;,
    0.274772;-10.346991;,
    0.218465;-10.346991;,
    0.164043;-10.346991;,
    0.001709;-10.346991;,
    0.612614;11.346992;,
    0.612614;7.008183;,
    0.725228;11.346992;,
    0.725228;7.008183;,
    0.781535;11.346992;,
    0.781535;7.008183;,
    0.842759;11.346992;,
    0.842759;7.008183;,
    0.996023;11.346992;,
    0.996023;7.008183;,
    0.612614;2.669394;,
    0.725228;2.669394;,
    0.781535;2.669394;,
    0.842759;2.669394;,
    0.996023;2.669394;,
    0.612614;-1.669394;,
    0.725228;-1.669394;,
    0.781535;-1.669394;,
    0.842759;-1.669394;,
    0.996023;-1.669394;,
    0.612614;-6.008182;,
    0.725228;-6.008182;,
    0.781535;-6.008182;,
    0.842759;-6.008182;,
    0.996023;-6.008182;,
    0.612614;-10.346991;,
    0.725228;-10.346991;,
    0.781535;-10.346991;,
    0.842759;-10.346991;,
    0.996023;-10.346991;,
    0.218465;11.346992;,
    0.218465;7.008183;,
    0.164043;11.346992;,
    0.164043;7.008183;,
    0.218465;7.008183;,
    0.218465;2.669394;,
    0.164043;7.008183;,
    0.164043;7.008183;,
    0.164043;2.669394;,
    0.001709;7.008183;,
    0.218465;2.669394;,
    0.218465;-1.669394;,
    0.164043;2.669394;,
    0.164043;2.669394;,
    0.164043;-1.669394;,
    0.001709;2.669394;,
    0.218465;-1.669394;,
    0.218465;-6.008182;,
    0.164043;-1.669394;,
    0.164043;-1.669394;,
    0.164043;-6.008182;,
    0.001709;-1.669394;,
    0.218465;-6.008182;,
    0.218465;-10.346991;,
    0.164043;-6.008182;,
    0.164043;-6.008182;,
    0.164043;-10.346991;,
    0.001709;-6.008182;,
    0.781535;11.346992;,
    0.781535;7.008183;,
    0.842759;11.346992;,
    0.842759;7.008183;,
    0.781535;7.008183;,
    0.842759;7.008183;,
    0.781535;2.669394;,
    0.842759;7.008183;,
    0.996023;7.008183;,
    0.842759;2.669394;,
    0.781535;2.669394;,
    0.842759;2.669394;,
    0.781535;-1.669394;,
    0.842759;2.669394;,
    0.996023;2.669394;,
    0.842759;-1.669394;,
    0.781535;-1.669394;,
    0.842759;-1.669394;,
    0.781535;-6.008182;,
    0.842759;-1.669394;,
    0.996023;-1.669394;,
    0.842759;-6.008182;,
    0.781535;-6.008182;,
    0.842759;-6.008182;,
    0.781535;-10.346991;,
    0.842759;-6.008182;,
    0.996023;-6.008182;,
    0.842759;-10.346991;;
   }

   MeshMaterialList {
    1;
    50;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0;

    Material lambert2SG {
     0.800000;0.800000;0.800000;1.000000;;
     0.000000;
     0.000000;0.000000;0.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      ".\\4-lane_2-way.bmp";
     }
    }
   }

   VertexDuplicationIndices {
    122;
    66;
    0,
    1,
    2,
    3,
    4,
    5,
    6,
    7,
    8,
    9,
    10,
    11,
    12,
    13,
    14,
    15,
    16,
    17,
    18,
    19,
    20,
    21,
    22,
    23,
    24,
    25,
    26,
    27,
    28,
    29,
    30,
    31,
    32,
    33,
    34,
    35,
    36,
    37,
    38,
    39,
    40,
    41,
    42,
    43,
    44,
    45,
    46,
    47,
    48,
    49,
    50,
    51,
    52,
    53,
    54,
    55,
    56,
    57,
    58,
    59,
    60,
    61,
    62,
    63,
    64,
    65,
    7,
    6,
    9,
    8,
    6,
    15,
    8,
    8,
    16,
    10,
    15,
    21,
    16,
    16,
    22,
    17,
    21,
    27,
    22,
    22,
    28,
    23,
    27,
    33,
    28,
    28,
    34,
    29,
    40,
    41,
    42,
    43,
    41,
    43,
    48,
    43,
    45,
    49,
    48,
    49,
    53,
    49,
    50,
    54,
    53,
    54,
    58,
    54,
    55,
    59,
    58,
    59,
    63,
    59,
    60,
    64;
   }
  }
 }
}

AnimationSet {
 
}