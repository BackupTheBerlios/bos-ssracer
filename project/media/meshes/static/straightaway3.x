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
   687.306946;0.000000;279.652313;,
   412.384186;0.000000;167.791412;,
   411.522614;0.000000;169.908844;,
   686.166016;0.000000;281.633270;,
   410.661102;0.000000;172.026276;,
   685.025024;0.000000;283.614166;,
   410.230316;0.000000;173.084991;,
   684.454590;0.000000;284.604645;,
   410.230316;0.400000;173.084991;,
   684.454590;0.400000;284.604645;,
   409.370056;0.400000;175.199310;,
   683.315369;0.400000;286.582642;,
   137.461395;0.000000;55.930466;,
   136.599854;0.000000;58.047901;,
   135.738297;0.000000;60.165340;,
   135.307526;0.000000;61.224056;,
   135.307526;0.400000;61.224056;,
   134.447250;0.400000;63.338364;,
   -137.461395;0.000000;-55.930466;,
   -138.322937;0.000000;-53.813030;,
   -139.184494;0.000000;-51.695595;,
   -139.615250;0.000000;-50.636875;,
   -139.615250;0.400000;-50.636875;,
   -140.475525;0.400000;-48.522568;,
   -412.384186;0.000000;-167.791412;,
   -413.245728;0.000000;-165.673965;,
   -414.107269;0.000000;-163.556534;,
   -414.538055;0.000000;-162.497818;,
   -414.538055;0.400000;-162.497818;,
   -415.398315;0.400000;-160.383514;,
   -687.306946;0.000000;-279.652313;,
   -688.168518;0.000000;-277.534882;,
   -689.030029;0.000000;-275.417450;,
   -689.460815;0.000000;-274.358734;,
   -689.460815;0.400000;-274.358734;,
   -690.321106;0.400000;-272.244415;,
   688.447876;0.000000;277.671387;,
   413.245728;0.000000;165.673965;,
   689.588806;0.000000;275.690460;,
   414.107269;0.000000;163.556534;,
   690.159302;0.000000;274.700012;,
   414.538055;0.000000;162.497818;,
   690.159302;0.400000;274.700012;,
   414.538055;0.400000;162.497818;,
   691.298523;0.400000;272.722015;,
   415.398315;0.400000;160.383514;,
   138.322937;0.000000;53.813030;,
   139.184494;0.000000;51.695595;,
   139.615250;0.000000;50.636875;,
   139.615250;0.400000;50.636875;,
   140.475525;0.400000;48.522568;,
   -136.599854;0.000000;-58.047901;,
   -135.738297;0.000000;-60.165340;,
   -135.307526;0.000000;-61.224056;,
   -135.307526;0.400000;-61.224056;,
   -134.447250;0.400000;-63.338364;,
   -411.522614;0.000000;-169.908844;,
   -410.661102;0.000000;-172.026276;,
   -410.230316;0.000000;-173.084991;,
   -410.230316;0.400000;-173.084991;,
   -409.370056;0.400000;-175.199310;,
   -686.445374;0.000000;-281.769745;,
   -685.583862;0.000000;-283.887207;,
   -685.153076;0.000000;-284.945923;,
   -685.153076;0.400000;-284.945923;,
   -684.292786;0.400000;-287.060211;,
   684.454590;0.000000;284.604645;,
   410.230316;0.000000;173.084991;,
   684.454590;0.400000;284.604645;,
   410.230316;0.400000;173.084991;,
   410.230316;0.000000;173.084991;,
   135.307526;0.000000;61.224056;,
   410.230316;0.400000;173.084991;,
   410.230316;0.400000;173.084991;,
   135.307526;0.400000;61.224056;,
   409.370056;0.400000;175.199310;,
   135.307526;0.000000;61.224056;,
   -139.615250;0.000000;-50.636875;,
   135.307526;0.400000;61.224056;,
   135.307526;0.400000;61.224056;,
   -139.615250;0.400000;-50.636875;,
   134.447250;0.400000;63.338364;,
   -139.615250;0.000000;-50.636875;,
   -414.538055;0.000000;-162.497818;,
   -139.615250;0.400000;-50.636875;,
   -139.615250;0.400000;-50.636875;,
   -414.538055;0.400000;-162.497818;,
   -140.475525;0.400000;-48.522568;,
   -414.538055;0.000000;-162.497818;,
   -689.460815;0.000000;-274.358734;,
   -414.538055;0.400000;-162.497818;,
   -414.538055;0.400000;-162.497818;,
   -689.460815;0.400000;-274.358734;,
   -415.398315;0.400000;-160.383514;,
   690.159302;0.000000;274.700012;,
   414.538055;0.000000;162.497818;,
   690.159302;0.400000;274.700012;,
   414.538055;0.400000;162.497818;,
   414.538055;0.000000;162.497818;,
   414.538055;0.400000;162.497818;,
   139.615250;0.000000;50.636875;,
   414.538055;0.400000;162.497818;,
   415.398315;0.400000;160.383514;,
   139.615250;0.400000;50.636875;,
   139.615250;0.000000;50.636875;,
   139.615250;0.400000;50.636875;,
   -135.307526;0.000000;-61.224056;,
   139.615250;0.400000;50.636875;,
   140.475525;0.400000;48.522568;,
   -135.307526;0.400000;-61.224056;,
   -135.307526;0.000000;-61.224056;,
   -135.307526;0.400000;-61.224056;,
   -410.230316;0.000000;-173.084991;,
   -135.307526;0.400000;-61.224056;,
   -134.447250;0.400000;-63.338364;,
   -410.230316;0.400000;-173.084991;,
   -410.230316;0.000000;-173.084991;,
   -410.230316;0.400000;-173.084991;,
   -685.153076;0.000000;-284.945923;,
   -410.230316;0.400000;-173.084991;,
   -409.370056;0.400000;-175.199310;,
   -685.153076;0.400000;-284.945923;;
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
    -0.377043;0.000006;0.926196;,
    -0.376879;-0.000008;0.926263;,
    -0.376879;-0.000008;0.926263;,
    -0.376879;0.000000;0.926263;,
    -0.376879;-0.000012;0.926263;,
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
    0.000000;1.000000;0.000000;,
    0.376713;0.000007;-0.926330;,
    0.376879;-0.000013;-0.926263;,
    0.376879;-0.000000;-0.926263;,
    0.376879;0.000008;-0.926263;,
    0.376879;0.000008;-0.926263;;
    50;
    4;13,13,13,13;,
    4;13,13,13,13;,
    4;13,13,13,13;,
    4;16,16,16,16;,
    4;10,10,10,10;,
    4;13,13,13,13;,
    4;13,13,13,13;,
    4;13,13,13,13;,
    4;20,20,20,20;,
    4;6,6,6,6;,
    4;13,13,13,13;,
    4;13,13,13,13;,
    4;13,13,13,13;,
    4;18,18,18,18;,
    4;5,5,5,5;,
    4;13,13,13,13;,
    4;13,13,13,13;,
    4;13,13,13,13;,
    4;19,19,19,19;,
    4;8,8,8,8;,
    4;13,13,13,13;,
    4;13,13,13,13;,
    4;13,13,13,13;,
    4;17,17,17,17;,
    4;14,14,14,14;,
    4;13,13,13,13;,
    4;13,13,13,13;,
    4;13,13,13,13;,
    4;0,0,0,0;,
    4;7,7,7,7;,
    4;13,13,13,13;,
    4;13,13,13,13;,
    4;13,13,13,13;,
    4;2,2,2,2;,
    4;12,12,12,12;,
    4;13,13,13,13;,
    4;13,13,13,13;,
    4;13,13,13,13;,
    4;3,3,3,3;,
    4;9,9,9,9;,
    4;13,13,13,13;,
    4;13,13,13,13;,
    4;13,13,13,13;,
    4;1,1,1,1;,
    4;11,11,11,11;,
    4;13,13,13,13;,
    4;13,13,13,13;,
    4;13,13,13,13;,
    4;4,4,4,4;,
    4;15,15,15,15;;
   }

   MeshTextureCoords {
    122;
    0.500000;22.747478;,
    0.500000;13.848459;,
    0.387386;13.848459;,
    0.387386;22.747478;,
    0.274772;13.848459;,
    0.274772;22.747478;,
    0.218465;13.848459;,
    0.218465;22.747478;,
    0.164043;13.848459;,
    0.164043;22.747478;,
    0.001709;13.848459;,
    0.001709;22.747478;,
    0.500000;5.087457;,
    0.387386;5.087457;,
    0.274772;5.087457;,
    0.218465;5.087457;,
    0.164043;5.087457;,
    0.001709;5.087457;,
    0.500000;-3.949494;,
    0.387386;-3.949494;,
    0.274772;-3.949494;,
    0.218465;-3.949494;,
    0.164043;-3.949494;,
    0.001709;-3.949494;,
    0.500000;-12.848469;,
    0.387386;-12.848469;,
    0.274772;-12.848469;,
    0.218465;-12.848469;,
    0.164043;-12.848469;,
    0.001709;-12.848469;,
    0.500000;-21.747494;,
    0.387386;-21.747494;,
    0.274772;-21.747494;,
    0.218465;-21.747494;,
    0.164043;-21.747494;,
    0.001709;-21.747494;,
    0.612614;22.747478;,
    0.612614;13.848459;,
    0.725228;22.747478;,
    0.725228;13.848459;,
    0.781535;22.747478;,
    0.781535;13.848459;,
    0.842759;22.747478;,
    0.842759;13.848459;,
    0.996023;22.747478;,
    0.996023;13.848459;,
    0.612614;5.087457;,
    0.725228;5.087457;,
    0.781535;5.087457;,
    0.842759;5.087457;,
    0.996023;5.087457;,
    0.612614;-3.949494;,
    0.725228;-3.949494;,
    0.781535;-3.949494;,
    0.842759;-3.949494;,
    0.996023;-3.949494;,
    0.612614;-12.848469;,
    0.725228;-12.848469;,
    0.781535;-12.848469;,
    0.842759;-12.848469;,
    0.996023;-12.848469;,
    0.612614;-21.747494;,
    0.725228;-21.747494;,
    0.781535;-21.747494;,
    0.842759;-21.747494;,
    0.996023;-21.747494;,
    0.218465;22.747478;,
    0.218465;13.848459;,
    0.164043;22.747478;,
    0.164043;13.848459;,
    0.218465;13.848459;,
    0.218465;5.087457;,
    0.164043;13.848459;,
    0.164043;13.848459;,
    0.164043;5.087457;,
    0.001709;13.848459;,
    0.218465;5.087457;,
    0.218465;-3.949494;,
    0.164043;5.087457;,
    0.164043;5.087457;,
    0.164043;-3.949494;,
    0.001709;5.087457;,
    0.218465;-3.949494;,
    0.218465;-12.848469;,
    0.164043;-3.949494;,
    0.164043;-3.949494;,
    0.164043;-12.848469;,
    0.001709;-3.949494;,
    0.218465;-12.848469;,
    0.218465;-21.747494;,
    0.164043;-12.848469;,
    0.164043;-12.848469;,
    0.164043;-21.747494;,
    0.001709;-12.848469;,
    0.781535;22.747478;,
    0.781535;13.848459;,
    0.842759;22.747478;,
    0.842759;13.848459;,
    0.781535;13.848459;,
    0.842759;13.848459;,
    0.781535;5.087457;,
    0.842759;13.848459;,
    0.996023;13.848459;,
    0.842759;5.087457;,
    0.781535;5.087457;,
    0.842759;5.087457;,
    0.781535;-3.949494;,
    0.842759;5.087457;,
    0.996023;5.087457;,
    0.842759;-3.949494;,
    0.781535;-3.949494;,
    0.842759;-3.949494;,
    0.781535;-12.848469;,
    0.842759;-3.949494;,
    0.996023;-3.949494;,
    0.842759;-12.848469;,
    0.781535;-12.848469;,
    0.842759;-12.848469;,
    0.781535;-21.747494;,
    0.842759;-12.848469;,
    0.996023;-12.848469;,
    0.842759;-21.747494;;
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