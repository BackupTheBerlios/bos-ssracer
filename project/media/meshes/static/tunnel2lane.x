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
   0.999945,0.000000,0.010472,0.000000,0.003912,0.927586,-0.373588,0.000000,-0.009713,0.373609,0.927536,0.000000,-0.684963,15.903893,35.867214,1.000000;;
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
   75;
   6.000000;0.000000;15.000000;,
   6.000000;2.000000;15.000000;,
   6.000000;2.000000;7.500000;,
   6.000000;0.000000;7.500000;,
   3.991501;4.000000;15.000000;,
   3.991501;4.000000;7.500000;,
   1.995751;5.000000;15.000000;,
   1.995751;5.000000;7.500000;,
   0.000000;5.000000;15.000000;,
   0.000000;5.000000;7.500000;,
   -1.995751;5.000000;15.000000;,
   -1.995751;5.000000;7.500000;,
   -3.991501;4.000000;15.000000;,
   -3.991501;4.000000;7.500000;,
   -6.000000;2.000000;15.000000;,
   -6.000000;2.000000;7.500000;,
   -6.000000;0.000000;15.000000;,
   -6.000000;0.000000;7.500000;,
   6.000000;2.000000;0.000000;,
   6.000000;0.000000;0.000000;,
   3.991501;4.000000;0.000000;,
   1.995751;5.000000;0.000000;,
   0.000000;5.000000;0.000000;,
   -1.995751;5.000000;0.000000;,
   -3.991501;4.000000;0.000000;,
   -6.000000;2.000000;0.000000;,
   -6.000000;0.000000;0.000000;,
   6.000000;2.000000;-7.500000;,
   6.000000;0.000000;-7.500000;,
   3.991501;4.000000;-7.500000;,
   1.995751;5.000000;-7.500000;,
   0.000000;5.000000;-7.500000;,
   -1.995751;5.000000;-7.500000;,
   -3.991501;4.000000;-7.500000;,
   -6.000000;2.000000;-7.500000;,
   -6.000000;0.000000;-7.500000;,
   6.000000;2.000000;-15.000000;,
   6.000000;0.000000;-15.000000;,
   3.991501;4.000000;-15.000000;,
   1.995751;5.000000;-15.000000;,
   0.000000;5.000000;-15.000000;,
   -1.995751;5.000000;-15.000000;,
   -3.991501;4.000000;-15.000000;,
   -6.000000;2.000000;-15.000000;,
   -6.000000;0.000000;-15.000000;,
   6.000000;2.000000;15.000000;,
   6.000000;2.000000;7.500000;,
   3.991501;4.000000;15.000000;,
   3.991501;4.000000;7.500000;,
   1.995751;5.000000;15.000000;,
   1.995751;5.000000;7.500000;,
   -1.995751;5.000000;15.000000;,
   -1.995751;5.000000;7.500000;,
   -3.991501;4.000000;15.000000;,
   -3.991501;4.000000;7.500000;,
   -6.000000;2.000000;15.000000;,
   -6.000000;2.000000;7.500000;,
   6.000000;2.000000;0.000000;,
   3.991501;4.000000;0.000000;,
   1.995751;5.000000;0.000000;,
   -1.995751;5.000000;0.000000;,
   -3.991501;4.000000;0.000000;,
   -6.000000;2.000000;0.000000;,
   6.000000;2.000000;-7.500000;,
   3.991501;4.000000;-7.500000;,
   1.995751;5.000000;-7.500000;,
   -1.995751;5.000000;-7.500000;,
   -3.991501;4.000000;-7.500000;,
   -6.000000;2.000000;-7.500000;,
   6.000000;2.000000;-15.000000;,
   3.991501;4.000000;-15.000000;,
   1.995751;5.000000;-15.000000;,
   -1.995751;5.000000;-15.000000;,
   -3.991501;4.000000;-15.000000;,
   -6.000000;2.000000;-15.000000;;
   32;
   4;3,2,1,0;,
   4;46,5,4,45;,
   4;48,7,6,47;,
   4;50,9,8,49;,
   4;9,11,10,8;,
   4;52,13,12,51;,
   4;54,15,14,53;,
   4;56,17,16,55;,
   4;19,18,2,3;,
   4;57,20,5,46;,
   4;58,21,7,48;,
   4;59,22,9,50;,
   4;22,23,11,9;,
   4;60,24,13,52;,
   4;61,25,15,54;,
   4;62,26,17,56;,
   4;28,27,18,19;,
   4;63,29,20,57;,
   4;64,30,21,58;,
   4;65,31,22,59;,
   4;31,32,23,22;,
   4;66,33,24,60;,
   4;67,34,25,61;,
   4;68,35,26,62;,
   4;37,36,27,28;,
   4;69,38,29,63;,
   4;70,39,30,64;,
   4;71,40,31,65;,
   4;40,41,32,31;,
   4;72,42,33,66;,
   4;73,43,34,67;,
   4;74,44,35,68;;

   MeshNormals {
    7;
    -1.000000;0.000000;0.000000;,
    -0.705606;-0.708604;-0.000000;,
    -0.447975;-0.894046;-0.000000;,
    0.000000;-1.000000;-0.000000;,
    0.447975;-0.894046;-0.000000;,
    0.705606;-0.708604;-0.000000;,
    1.000000;0.000000;0.000000;;
    32;
    4;0,0,0,0;,
    4;1,1,1,1;,
    4;2,2,2,2;,
    4;3,3,3,3;,
    4;3,3,3,3;,
    4;4,4,4,4;,
    4;5,5,5,5;,
    4;6,6,6,6;,
    4;0,0,0,0;,
    4;1,1,1,1;,
    4;2,2,2,2;,
    4;3,3,3,3;,
    4;3,3,3,3;,
    4;4,4,4,4;,
    4;5,5,5,5;,
    4;6,6,6,6;,
    4;0,0,0,0;,
    4;1,1,1,1;,
    4;2,2,2,2;,
    4;3,3,3,3;,
    4;3,3,3,3;,
    4;4,4,4,4;,
    4;5,5,5,5;,
    4;6,6,6,6;,
    4;0,0,0,0;,
    4;1,1,1,1;,
    4;2,2,2,2;,
    4;3,3,3,3;,
    4;3,3,3,3;,
    4;4,4,4,4;,
    4;5,5,5,5;,
    4;6,6,6,6;;
   }

   MeshTextureCoords {
    75;
    -1.427578;-1.417022;,
    -1.426258;-0.936446;,
    -0.465109;-0.939085;,
    -0.466429;-1.419661;,
    -1.424938;-0.455871;,
    -0.463789;-0.458511;,
    -1.423619;0.024703;,
    -0.462469;0.022065;,
    -1.422300;0.505278;,
    -0.461150;0.502639;,
    -1.420980;0.985853;,
    -0.459830;0.983214;,
    -1.419660;1.466428;,
    -0.458511;1.463789;,
    -1.418342;1.947003;,
    -0.457191;1.944363;,
    -1.417022;2.427578;,
    -0.455871;2.424939;,
    0.496041;-0.941725;,
    0.494722;-1.422300;,
    0.497361;-0.461150;,
    0.498681;0.019425;,
    0.500000;0.500000;,
    0.501320;0.980575;,
    0.502639;1.461150;,
    0.503959;1.941726;,
    0.505278;2.422300;,
    1.457191;-0.944363;,
    1.455871;-1.424938;,
    1.458511;-0.463789;,
    1.459830;0.016785;,
    1.461150;0.497360;,
    1.462469;0.977935;,
    1.463788;1.458511;,
    1.465108;1.939085;,
    1.466429;2.419660;,
    2.418343;-0.947004;,
    2.417021;-1.427578;,
    2.419660;-0.466429;,
    2.420979;0.014146;,
    2.422300;0.494722;,
    2.423619;0.975297;,
    2.424939;1.455871;,
    2.426258;1.936446;,
    2.427577;2.417021;,
    -1.426258;-0.936446;,
    -0.465109;-0.939085;,
    -1.424938;-0.455871;,
    -0.463789;-0.458511;,
    -1.423619;0.024703;,
    -0.462469;0.022065;,
    -1.420980;0.985853;,
    -0.459830;0.983214;,
    -1.419660;1.466428;,
    -0.458511;1.463789;,
    -1.418342;1.947003;,
    -0.457191;1.944363;,
    0.496041;-0.941725;,
    0.497361;-0.461150;,
    0.498681;0.019425;,
    0.501320;0.980575;,
    0.502639;1.461150;,
    0.503959;1.941726;,
    1.457191;-0.944363;,
    1.458511;-0.463789;,
    1.459830;0.016785;,
    1.462469;0.977935;,
    1.463788;1.458511;,
    1.465108;1.939085;,
    2.418343;-0.947004;,
    2.419660;-0.466429;,
    2.420979;0.014146;,
    2.423619;0.975297;,
    2.424939;1.455871;,
    2.426258;1.936446;;
   }

   MeshMaterialList {
    1;
    32;
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
      "tunnelwall.bmp";
     }
    }
   }

   VertexDuplicationIndices {
    75;
    45;
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
    1,
    2,
    4,
    5,
    6,
    7,
    10,
    11,
    12,
    13,
    14,
    15,
    18,
    20,
    21,
    23,
    24,
    25,
    27,
    29,
    30,
    32,
    33,
    34,
    36,
    38,
    39,
    41,
    42,
    43;
   }
  }
 }
}

AnimationSet {
 
}