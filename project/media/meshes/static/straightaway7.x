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
   1.000000,0.000000,0.000000,0.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,2.948164,100.000000,-0.485961,1.000000;;
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
   120;
   444.096100;0.000000;-5.833067;,
   266.457672;0.000000;-3.499840;,
   266.486786;0.000000;-1.281621;,
   443.939270;0.000000;-3.632931;,
   266.515930;0.000000;0.936599;,
   443.782471;0.000000;-1.432793;,
   266.530518;0.000000;2.045709;,
   443.704071;0.000000;-0.332724;,
   266.530518;0.388173;2.045709;,
   443.704071;0.388173;-0.332724;,
   266.559601;0.388173;4.260650;,
   443.547485;0.388173;1.864161;,
   88.819221;0.000000;-1.166613;,
   88.848351;0.000000;1.051606;,
   88.877495;0.000000;3.269826;,
   88.892059;0.000000;4.378936;,
   88.892059;0.388173;4.378936;,
   88.921150;0.388173;6.593877;,
   -88.819221;0.000000;1.166613;,
   -88.790085;0.000000;3.384833;,
   -88.760948;0.000000;5.603053;,
   -88.746384;0.000000;6.712163;,
   -88.746384;0.388173;6.712163;,
   -88.717285;0.388173;8.927103;,
   -266.457672;0.000000;3.499840;,
   -266.428528;0.000000;5.718060;,
   -266.399384;0.000000;7.936279;,
   -266.384827;0.000000;9.045389;,
   -266.384827;0.388173;9.045389;,
   -266.355743;0.388173;11.260330;,
   -444.096100;0.000000;5.833067;,
   -444.066956;0.000000;8.051287;,
   -444.037811;0.000000;10.269506;,
   -444.023254;0.000000;11.378616;,
   -444.023254;0.388173;11.378616;,
   -443.994141;0.388173;13.593557;,
   444.252899;0.000000;-8.033203;,
   266.428528;0.000000;-5.718060;,
   444.409668;0.000000;-10.233339;,
   266.399384;0.000000;-7.936279;,
   444.488098;0.000000;-11.333408;,
   266.384827;0.000000;-9.045389;,
   444.488098;0.388173;-11.333408;,
   266.384827;0.388173;-9.045389;,
   444.644684;0.388173;-13.530294;,
   266.355743;0.388173;-11.260330;,
   88.790085;0.000000;-3.384833;,
   88.760948;0.000000;-5.603053;,
   88.746384;0.000000;-6.712163;,
   88.746384;0.388173;-6.712163;,
   88.717285;0.388173;-8.927103;,
   -88.848351;0.000000;-1.051606;,
   -88.877495;0.000000;-3.269826;,
   -88.892059;0.000000;-4.378936;,
   -88.892059;0.388173;-4.378936;,
   -88.921150;0.388173;-6.593877;,
   -266.486786;0.000000;1.281621;,
   -266.515930;0.000000;-0.936599;,
   -266.530518;0.000000;-2.045709;,
   -266.530518;0.388173;-2.045709;,
   -266.559601;0.388173;-4.260650;,
   -444.125214;0.000000;3.614847;,
   -444.154358;0.000000;1.396627;,
   -444.168915;0.000000;0.287518;,
   -444.168915;0.388173;0.287518;,
   -444.198029;0.388173;-1.927423;,
   443.704071;0.000000;-0.332724;,
   266.530518;0.000000;2.045709;,
   443.704071;0.388173;-0.332724;,
   266.530518;0.388173;2.045709;,
   266.530518;0.000000;2.045709;,
   88.892059;0.000000;4.378936;,
   266.530518;0.388173;2.045709;,
   266.530518;0.388173;2.045709;,
   88.892059;0.388173;4.378936;,
   266.559601;0.388173;4.260650;,
   88.892059;0.000000;4.378936;,
   -88.746384;0.000000;6.712163;,
   88.892059;0.388173;4.378936;,
   88.892059;0.388173;4.378936;,
   -88.746384;0.388173;6.712163;,
   88.921150;0.388173;6.593877;,
   -88.746384;0.000000;6.712163;,
   -266.384827;0.000000;9.045389;,
   -88.746384;0.388173;6.712163;,
   -88.746384;0.388173;6.712163;,
   -266.384827;0.388173;9.045389;,
   -88.717285;0.388173;8.927103;,
   -266.384827;0.000000;9.045389;,
   -444.023254;0.000000;11.378616;,
   -266.384827;0.388173;9.045389;,
   -266.384827;0.388173;9.045389;,
   -444.023254;0.388173;11.378616;,
   -266.355743;0.388173;11.260330;,
   444.488098;0.000000;-11.333408;,
   266.384827;0.000000;-9.045389;,
   444.488098;0.388173;-11.333408;,
   266.384827;0.388173;-9.045389;,
   266.384827;0.000000;-9.045389;,
   266.384827;0.388173;-9.045389;,
   88.746384;0.000000;-6.712163;,
   266.384827;0.388173;-9.045389;,
   266.355743;0.388173;-11.260330;,
   88.746384;0.388173;-6.712163;,
   88.746384;0.000000;-6.712163;,
   88.746384;0.388173;-6.712163;,
   -88.892059;0.000000;-4.378936;,
   -88.892059;0.388173;-4.378936;,
   -88.892059;0.000000;-4.378936;,
   -88.892059;0.388173;-4.378936;,
   -266.530518;0.000000;-2.045709;,
   -88.892059;0.388173;-4.378936;,
   -88.921150;0.388173;-6.593877;,
   -266.530518;0.388173;-2.045709;,
   -266.530518;0.000000;-2.045709;,
   -266.530518;0.388173;-2.045709;,
   -444.168915;0.000000;0.287518;,
   -266.530518;0.388173;-2.045709;,
   -266.559601;0.388173;-4.260650;,
   -444.168915;0.388173;0.287518;;
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
   4;107,55,50,103;,
   4;24,56,51,18;,
   4;56,57,52,51;,
   4;57,58,53,52;,
   4;110,59,109,108;,
   4;113,60,112,111;,
   4;30,61,56,24;,
   4;61,62,57,56;,
   4;62,63,58,57;,
   4;116,64,115,114;,
   4;119,65,118,117;;

   MeshNormals {
    20;
    -0.013423;-0.000000;-0.999910;,
    -0.013134;0.000000;-0.999914;,
    -0.013134;0.000000;-0.999914;,
    -0.013134;-0.000000;-0.999914;,
    -0.013134;-0.000000;-0.999914;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.012846;0.000000;0.999918;,
    0.013134;0.000000;0.999914;,
    0.013134;0.000000;0.999914;,
    0.013134;-0.000000;0.999914;,
    0.013134;-0.000000;0.999914;;
    50;
    4;8,8,8,8;,
    4;8,8,8,8;,
    4;8,8,8,8;,
    4;0,0,0,0;,
    4;9,9,9,9;,
    4;8,8,8,8;,
    4;8,8,8,8;,
    4;8,8,8,8;,
    4;2,2,2,2;,
    4;7,7,7,7;,
    4;8,8,8,8;,
    4;8,8,8,8;,
    4;8,8,8,8;,
    4;3,3,3,3;,
    4;14,14,14,14;,
    4;8,8,8,8;,
    4;8,8,8,8;,
    4;8,8,8,8;,
    4;4,4,4,4;,
    4;10,10,10,10;,
    4;8,8,8,8;,
    4;8,8,8,8;,
    4;8,8,8,8;,
    4;1,1,1,1;,
    4;12,12,12,12;,
    4;8,8,8,8;,
    4;8,8,8,8;,
    4;8,8,8,8;,
    4;15,15,15,15;,
    4;5,5,5,5;,
    4;8,8,8,8;,
    4;8,8,8,8;,
    4;8,8,8,8;,
    4;16,16,16,16;,
    4;11,11,11,11;,
    4;8,8,8,8;,
    4;8,8,8,8;,
    4;8,8,8,8;,
    4;17,17,17,17;,
    4;11,11,11,11;,
    4;8,8,8,8;,
    4;8,8,8,8;,
    4;8,8,8,8;,
    4;18,18,18,18;,
    4;6,6,6,6;,
    4;8,8,8,8;,
    4;8,8,8,8;,
    4;8,8,8,8;,
    4;19,19,19,19;,
    4;13,13,13,13;;
   }

   MeshTextureCoords {
    120;
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
    120;
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