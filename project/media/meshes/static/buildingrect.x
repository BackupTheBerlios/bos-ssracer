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
   0.956305,-0.000000,0.292372,0.000000,0.010909,0.999304,-0.035682,0.000000,-0.292168,0.037313,0.955639,0.000000,-41.128880,4.900502,121.627800,1.000000;;
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
   66;
   -7.500000;0.000000;5.000000;,
   0.000000;0.000000;5.000000;,
   0.000000;4.000000;5.000000;,
   -7.500000;4.000000;5.000000;,
   7.500000;0.000000;5.000000;,
   7.500000;4.000000;5.000000;,
   0.000000;19.500000;5.000000;,
   -7.500000;19.500000;5.000000;,
   7.500000;19.500000;5.000000;,
   0.000000;34.000000;5.000000;,
   -7.500000;34.000000;5.000000;,
   7.500000;34.000000;5.000000;,
   0.000000;34.000000;0.000000;,
   -7.500000;34.000000;0.000000;,
   7.500000;34.000000;0.000000;,
   0.000000;34.000000;-5.000000;,
   -7.500000;34.000000;-5.000000;,
   7.500000;34.000000;-5.000000;,
   0.000000;19.500000;-5.000000;,
   -7.500000;19.500000;-5.000000;,
   7.500000;19.500000;-5.000000;,
   0.000000;4.000000;-5.000000;,
   -7.500000;4.000000;-5.000000;,
   7.500000;4.000000;-5.000000;,
   0.000000;0.000000;-5.000000;,
   -7.500000;0.000000;-5.000000;,
   7.500000;0.000000;-5.000000;,
   0.000000;0.000000;0.000000;,
   -7.500000;0.000000;0.000000;,
   7.500000;0.000000;0.000000;,
   7.500000;4.000000;0.000000;,
   7.500000;19.500000;0.000000;,
   -7.500000;4.000000;0.000000;,
   -7.500000;19.500000;0.000000;,
   -7.500000;34.000000;5.000000;,
   0.000000;34.000000;5.000000;,
   7.500000;34.000000;5.000000;,
   -7.500000;34.000000;-5.000000;,
   0.000000;34.000000;-5.000000;,
   7.500000;34.000000;-5.000000;,
   -7.500000;0.000000;-5.000000;,
   0.000000;0.000000;-5.000000;,
   7.500000;0.000000;-5.000000;,
   0.000000;0.000000;5.000000;,
   -7.500000;0.000000;5.000000;,
   7.500000;0.000000;5.000000;,
   7.500000;0.000000;0.000000;,
   7.500000;0.000000;-5.000000;,
   7.500000;4.000000;-5.000000;,
   7.500000;0.000000;5.000000;,
   7.500000;4.000000;5.000000;,
   7.500000;19.500000;-5.000000;,
   7.500000;19.500000;5.000000;,
   7.500000;34.000000;-5.000000;,
   7.500000;34.000000;0.000000;,
   7.500000;34.000000;5.000000;,
   -7.500000;0.000000;-5.000000;,
   -7.500000;0.000000;0.000000;,
   -7.500000;4.000000;-5.000000;,
   -7.500000;0.000000;5.000000;,
   -7.500000;4.000000;5.000000;,
   -7.500000;19.500000;-5.000000;,
   -7.500000;19.500000;5.000000;,
   -7.500000;34.000000;0.000000;,
   -7.500000;34.000000;-5.000000;,
   -7.500000;34.000000;5.000000;;
   32;
   4;3,2,1,0;,
   4;2,5,4,1;,
   4;7,6,2,3;,
   4;6,8,5,2;,
   4;10,9,6,7;,
   4;9,11,8,6;,
   4;13,12,35,34;,
   4;12,14,36,35;,
   4;16,15,12,13;,
   4;15,17,14,12;,
   4;19,18,38,37;,
   4;18,20,39,38;,
   4;22,21,18,19;,
   4;21,23,20,18;,
   4;25,24,21,22;,
   4;24,26,23,21;,
   4;28,27,41,40;,
   4;27,29,42,41;,
   4;44,43,27,28;,
   4;43,45,29,27;,
   4;30,48,47,46;,
   4;50,30,46,49;,
   4;31,51,48,30;,
   4;52,31,30,50;,
   4;54,53,51,31;,
   4;55,54,31,52;,
   4;58,32,57,56;,
   4;32,60,59,57;,
   4;61,33,32,58;,
   4;33,62,60,32;,
   4;64,63,33,61;,
   4;63,65,62,33;;

   MeshNormals {
    6;
    -1.000000;0.000000;0.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;0.000000;-1.000000;,
    0.000000;0.000000;1.000000;,
    0.000000;1.000000;0.000000;,
    1.000000;0.000000;0.000000;;
    32;
    4;3,3,3,3;,
    4;3,3,3,3;,
    4;3,3,3,3;,
    4;3,3,3,3;,
    4;3,3,3,3;,
    4;3,3,3,3;,
    4;4,4,4,4;,
    4;4,4,4,4;,
    4;4,4,4,4;,
    4;4,4,4,4;,
    4;2,2,2,2;,
    4;2,2,2,2;,
    4;2,2,2,2;,
    4;2,2,2,2;,
    4;2,2,2,2;,
    4;2,2,2,2;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;5,5,5,5;,
    4;5,5,5,5;,
    4;5,5,5,5;,
    4;5,5,5,5;,
    4;5,5,5,5;,
    4;5,5,5,5;,
    4;0,0,0,0;,
    4;0,0,0,0;,
    4;0,0,0,0;,
    4;0,0,0,0;,
    4;0,0,0,0;,
    4;0,0,0,0;;
   }

   MeshTextureCoords {
    66;
    -1.296455;2.500000;,
    0.500000;2.500000;,
    0.500000;2.462513;,
    -1.296455;2.462513;,
    2.296454;2.500000;,
    2.296454;2.462513;,
    0.500000;0.122594;,
    -1.296455;0.122594;,
    2.296454;0.122594;,
    0.500000;-2.066363;,
    -1.296455;-2.066363;,
    2.296454;-2.066363;,
    0.500000;-2.066363;,
    -2.410671;-2.066363;,
    3.614058;-2.066363;,
    0.500000;-2.066363;,
    -1.296455;-2.066363;,
    2.296454;-2.066363;,
    0.500000;0.122594;,
    -1.296455;0.122594;,
    2.296454;0.122594;,
    0.500000;2.462513;,
    -1.296455;2.462513;,
    2.296454;2.462513;,
    0.500000;2.500000;,
    -1.296455;2.500000;,
    2.296454;2.500000;,
    0.500000;2.500000;,
    -2.410671;2.500000;,
    3.614058;2.500000;,
    3.614058;2.462513;,
    3.614058;0.122594;,
    -2.410671;2.462513;,
    -2.410671;0.122594;,
    -1.296455;-2.066363;,
    0.500000;-2.066363;,
    2.296454;-2.066363;,
    -1.296455;-2.066363;,
    0.500000;-2.066363;,
    2.296454;-2.066363;,
    -1.296455;2.500000;,
    0.500000;2.500000;,
    2.296454;2.500000;,
    0.500000;2.500000;,
    -1.296455;2.500000;,
    2.296454;2.500000;,
    3.614058;2.500000;,
    2.296454;2.500000;,
    2.296454;2.462513;,
    2.296454;2.500000;,
    2.296454;2.462513;,
    2.296454;0.122594;,
    2.296454;0.122594;,
    2.296454;-2.066363;,
    3.614058;-2.066363;,
    2.296454;-2.066363;,
    -1.296455;2.500000;,
    -2.410671;2.500000;,
    -1.296455;2.462513;,
    -1.296455;2.500000;,
    -1.296455;2.462513;,
    -1.296455;0.122594;,
    -1.296455;0.122594;,
    -2.410671;-2.066363;,
    -1.296455;-2.066363;,
    -1.296455;-2.066363;;
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
      "building_green.bmp";
     }
    }
   }

   VertexDuplicationIndices {
    66;
    34;
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
    10,
    9,
    11,
    16,
    15,
    17,
    25,
    24,
    26,
    1,
    0,
    4,
    29,
    26,
    23,
    4,
    5,
    20,
    8,
    17,
    14,
    11,
    25,
    28,
    22,
    0,
    3,
    19,
    7,
    13,
    16,
    10;
   }
  }
 }
}

AnimationSet {
 
}