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

 Frame polySurface1 {
  

  FrameTransformMatrix {
   1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.000000,0.000000,1.000000;;
  }

  Mesh polySurfaceShape1 {
   122;
   8.871839;0.000000;17.104328;,
   5.323103;0.000000;10.262597;,
   3.293838;0.000000;11.315156;,
   6.842573;0.000000;18.156887;,
   1.264573;0.000000;12.367714;,
   4.813308;0.000000;19.209446;,
   0.249941;0.000000;12.893993;,
   3.798676;0.000000;19.735725;,
   0.249941;0.400000;12.893993;,
   3.798676;0.400000;19.735725;,
   -1.776325;0.400000;13.944997;,
   1.772411;0.400000;20.786728;,
   1.774368;0.000000;3.420866;,
   -0.254897;0.000000;4.473424;,
   -2.284162;0.000000;5.525983;,
   -3.298795;0.000000;6.052262;,
   -3.298795;0.400000;6.052262;,
   -5.325060;0.400000;7.103266;,
   -1.774368;0.000000;-3.420866;,
   -3.803633;0.000000;-2.368307;,
   -5.832898;0.000000;-1.315748;,
   -6.847530;0.000000;-0.789469;,
   -6.847530;0.400000;-0.789469;,
   -8.873796;0.400000;0.261534;,
   -5.323103;0.000000;-10.262597;,
   -7.352368;0.000000;-9.210038;,
   -9.381633;0.000000;-8.157479;,
   -10.396265;0.000000;-7.631200;,
   -10.396265;0.400000;-7.631200;,
   -12.422531;0.400000;-6.580197;,
   -9.113472;0.000000;-17.788496;,
   -11.132104;0.000000;-16.905581;,
   -13.150743;0.000000;-16.022684;,
   -14.160059;0.000000;-15.581227;,
   -14.160059;0.400000;-15.581227;,
   -16.175711;0.388173;-14.699625;,
   10.901103;0.000000;16.051769;,
   7.352368;0.000000;9.210038;,
   12.930368;0.000000;14.999209;,
   9.381633;0.000000;8.157479;,
   13.945001;0.000000;14.472930;,
   10.396265;0.000000;7.631200;,
   13.945001;0.400000;14.472930;,
   10.396265;0.400000;7.631200;,
   15.971266;0.400000;13.421927;,
   12.422531;0.400000;6.580197;,
   3.803633;0.000000;2.368307;,
   5.832898;0.000000;1.315748;,
   6.847530;0.000000;0.789469;,
   6.847530;0.400000;0.789469;,
   8.873796;0.400000;-0.261534;,
   0.254897;0.000000;-4.473424;,
   2.284162;0.000000;-5.525983;,
   3.298795;0.000000;-6.052262;,
   3.298795;0.400000;-6.052262;,
   5.325060;0.400000;-7.103266;,
   -3.293838;0.000000;-11.315156;,
   -1.264573;0.000000;-12.367714;,
   -0.249941;0.000000;-12.893993;,
   -0.249941;0.400000;-12.893993;,
   1.776325;0.400000;-13.944997;,
   -7.094841;0.000000;-18.671412;,
   -5.076210;0.000000;-19.554325;,
   -4.066884;0.000000;-19.995766;,
   -4.066884;0.400000;-19.995766;,
   -2.051233;0.388173;-20.877367;,
   3.798676;0.000000;19.735725;,
   0.249941;0.000000;12.893993;,
   3.798676;0.400000;19.735725;,
   0.249941;0.400000;12.893993;,
   0.249941;0.000000;12.893993;,
   -3.298795;0.000000;6.052262;,
   0.249941;0.400000;12.893993;,
   0.249941;0.400000;12.893993;,
   -3.298795;0.400000;6.052262;,
   -1.776325;0.400000;13.944997;,
   -3.298795;0.000000;6.052262;,
   -6.847530;0.000000;-0.789469;,
   -3.298795;0.400000;6.052262;,
   -3.298795;0.400000;6.052262;,
   -6.847530;0.400000;-0.789469;,
   -5.325060;0.400000;7.103266;,
   -6.847530;0.000000;-0.789469;,
   -10.396265;0.000000;-7.631200;,
   -6.847530;0.400000;-0.789469;,
   -6.847530;0.400000;-0.789469;,
   -10.396265;0.400000;-7.631200;,
   -8.873796;0.400000;0.261534;,
   -10.396265;0.000000;-7.631200;,
   -14.160059;0.000000;-15.581227;,
   -10.396265;0.400000;-7.631200;,
   -10.396265;0.400000;-7.631200;,
   -14.160059;0.400000;-15.581227;,
   -12.422531;0.400000;-6.580197;,
   13.945001;0.000000;14.472930;,
   10.396265;0.000000;7.631200;,
   13.945001;0.400000;14.472930;,
   10.396265;0.400000;7.631200;,
   10.396265;0.000000;7.631200;,
   10.396265;0.400000;7.631200;,
   6.847530;0.000000;0.789469;,
   10.396265;0.400000;7.631200;,
   12.422531;0.400000;6.580197;,
   6.847530;0.400000;0.789469;,
   6.847530;0.000000;0.789469;,
   6.847530;0.400000;0.789469;,
   3.298795;0.000000;-6.052262;,
   6.847530;0.400000;0.789469;,
   8.873796;0.400000;-0.261534;,
   3.298795;0.400000;-6.052262;,
   3.298795;0.000000;-6.052262;,
   3.298795;0.400000;-6.052262;,
   -0.249941;0.000000;-12.893993;,
   3.298795;0.400000;-6.052262;,
   5.325060;0.400000;-7.103266;,
   -0.249941;0.400000;-12.893993;,
   -0.249941;0.000000;-12.893993;,
   -0.249941;0.400000;-12.893993;,
   -4.066884;0.000000;-19.995766;,
   -0.249941;0.400000;-12.893993;,
   1.776325;0.400000;-13.944997;,
   -4.066884;0.400000;-19.995766;;
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
    -0.887692;-0.000000;0.460437;,
    -0.887692;0.000000;0.460437;,
    -0.887692;-0.000000;0.460437;,
    -0.887692;0.000001;0.460437;,
    -0.880838;0.000000;0.473418;,
    -0.002679;0.999996;0.000517;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.002002;0.999996;-0.001933;,
    0.887692;0.000000;-0.460437;,
    0.887692;-0.000000;-0.460437;,
    0.887692;-0.000000;-0.460437;,
    0.887692;0.000000;-0.460437;,
    0.903826;0.000000;-0.427900;;
    50;
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;18,18,18,18;,
    4;13,13,13,13;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;16,16,16,16;,
    4;6,6,6,6;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;17,17,17,17;,
    4;14,14,14,14;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;19,19,19,19;,
    4;8,8,8,8;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;20,20,20,20;,
    4;5,5,5,5;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;3,3,3,3;,
    4;11,11,11,11;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;0,0,0,0;,
    4;12,12,12,12;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;1,1,1,1;,
    4;7,7,7,7;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;2,2,2,2;,
    4;9,9,9,9;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;4,4,4,4;,
    4;15,15,15,15;;
   }

   MeshTextureCoords {
    122;
    0.500000;1.505270;,
    0.500000;1.103161;,
    0.387386;1.103161;,
    0.387386;1.505270;,
    0.274772;1.103161;,
    0.274772;1.505270;,
    0.218465;1.103161;,
    0.218465;1.505270;,
    0.164043;1.103161;,
    0.164043;1.505270;,
    0.001709;1.103161;,
    0.001709;1.505270;,
    0.500000;0.701054;,
    0.387386;0.701054;,
    0.274772;0.701054;,
    0.218465;0.701054;,
    0.164043;0.701054;,
    0.001709;0.701054;,
    0.500000;0.298946;,
    0.387386;0.298946;,
    0.274772;0.298946;,
    0.218465;0.298946;,
    0.164043;0.298946;,
    0.001709;0.298946;,
    0.500000;-0.103161;,
    0.387386;-0.103161;,
    0.274772;-0.103161;,
    0.218465;-0.103161;,
    0.164043;-0.103161;,
    0.001709;-0.103161;,
    0.500000;-0.505270;,
    0.387386;-0.505270;,
    0.274772;-0.505270;,
    0.218465;-0.505270;,
    0.164043;-0.505270;,
    0.001709;-0.505270;,
    0.612614;1.505270;,
    0.612614;1.103161;,
    0.725228;1.505270;,
    0.725228;1.103161;,
    0.781535;1.505270;,
    0.781535;1.103161;,
    0.842759;1.505270;,
    0.842759;1.103161;,
    0.996023;1.505270;,
    0.996023;1.103161;,
    0.612614;0.701054;,
    0.725228;0.701054;,
    0.781535;0.701054;,
    0.842759;0.701054;,
    0.996023;0.701054;,
    0.612614;0.298946;,
    0.725228;0.298946;,
    0.781535;0.298946;,
    0.842759;0.298946;,
    0.996023;0.298946;,
    0.612614;-0.103161;,
    0.725228;-0.103161;,
    0.781535;-0.103161;,
    0.842759;-0.103161;,
    0.996023;-0.103161;,
    0.612614;-0.505270;,
    0.725228;-0.505270;,
    0.781535;-0.505270;,
    0.842759;-0.505270;,
    0.996023;-0.505270;,
    0.218465;1.505270;,
    0.218465;1.103161;,
    0.164043;1.505270;,
    0.164043;1.103161;,
    0.218465;1.103161;,
    0.218465;0.701054;,
    0.164043;1.103161;,
    0.164043;1.103161;,
    0.164043;0.701054;,
    0.001709;1.103161;,
    0.218465;0.701054;,
    0.218465;0.298946;,
    0.164043;0.701054;,
    0.164043;0.701054;,
    0.164043;0.298946;,
    0.001709;0.701054;,
    0.218465;0.298946;,
    0.218465;-0.103161;,
    0.164043;0.298946;,
    0.164043;0.298946;,
    0.164043;-0.103161;,
    0.001709;0.298946;,
    0.218465;-0.103161;,
    0.218465;-0.505270;,
    0.164043;-0.103161;,
    0.164043;-0.103161;,
    0.164043;-0.505270;,
    0.001709;-0.103161;,
    0.781535;1.505270;,
    0.781535;1.103161;,
    0.842759;1.505270;,
    0.842759;1.103161;,
    0.781535;1.103161;,
    0.842759;1.103161;,
    0.781535;0.701054;,
    0.842759;1.103161;,
    0.996023;1.103161;,
    0.842759;0.701054;,
    0.781535;0.701054;,
    0.842759;0.701054;,
    0.781535;0.298946;,
    0.842759;0.701054;,
    0.996023;0.701054;,
    0.842759;0.298946;,
    0.781535;0.298946;,
    0.842759;0.298946;,
    0.781535;-0.103161;,
    0.842759;0.298946;,
    0.996023;0.298946;,
    0.842759;-0.103161;,
    0.781535;-0.103161;,
    0.842759;-0.103161;,
    0.781535;-0.505270;,
    0.842759;-0.103161;,
    0.996023;-0.103161;,
    0.842759;-0.505270;;
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
}

AnimationSet {
 
}