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
   0.596225,0.000000,-0.802817,0.000000,-0.368689,0.888310,-0.273813,0.000000,0.713151,0.459244,0.529633,0.000000,11.063270,8.371949,13.971726,1.000000;;
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
   36;
   0.025000;0.600000;15.000000;,
   -0.025000;0.600000;15.000000;,
   -0.100000;0.150000;15.000000;,
   -0.150000;0.000000;15.000000;,
   0.150000;0.000000;15.000000;,
   0.100000;0.150000;15.000000;,
   0.025000;0.600000;-15.000000;,
   -0.025000;0.600000;-15.000000;,
   0.100000;0.150000;-15.000000;,
   -0.150000;0.000000;-15.000000;,
   -0.100000;0.150000;-15.000000;,
   0.150000;0.000000;-15.000000;,
   -0.025000;0.600000;15.000000;,
   0.025000;0.600000;15.000000;,
   0.025000;0.600000;15.000000;,
   0.100000;0.150000;15.000000;,
   0.025000;0.600000;-15.000000;,
   -0.025000;0.600000;-15.000000;,
   0.025000;0.600000;-15.000000;,
   0.100000;0.150000;-15.000000;,
   -0.100000;0.150000;-15.000000;,
   -0.150000;0.000000;-15.000000;,
   -0.150000;0.000000;15.000000;,
   -0.100000;0.150000;15.000000;,
   -0.150000;0.000000;-15.000000;,
   0.150000;0.000000;-15.000000;,
   0.150000;0.000000;15.000000;,
   -0.150000;0.000000;15.000000;,
   0.150000;0.000000;15.000000;,
   0.150000;0.000000;-15.000000;,
   0.100000;0.150000;-15.000000;,
   0.100000;0.150000;15.000000;,
   -0.100000;0.150000;-15.000000;,
   -0.100000;0.150000;15.000000;,
   -0.025000;0.600000;15.000000;,
   -0.025000;0.600000;-15.000000;;
   8;
   6;5,4,3,2,1,0;,
   4;7,6,13,12;,
   4;16,8,15,14;,
   6;11,19,18,17,10,9;,
   4;23,22,21,20;,
   4;27,26,25,24;,
   4;31,30,29,28;,
   4;35,34,33,32;;

   MeshNormals {
    8;
    -0.986394;0.164399;0.000000;,
    -0.948683;0.316228;-0.000000;,
    -0.000003;0.000000;-1.000000;,
    0.000000;-1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000007;0.000000;1.000000;,
    0.948683;0.316228;-0.000000;,
    0.986394;0.164399;0.000000;;
    8;
    6;5,5,5,5,5,5;,
    4;4,4,4,4;,
    4;7,7,7,7;,
    6;2,2,2,2,2,2;,
    4;1,1,1,1;,
    4;3,3,3,3;,
    4;6,6,6,6;,
    4;0,0,0,0;;
   }

   MeshTextureCoords {
    36;
    -5.983133;0.100000;,
    -5.983133;0.100000;,
    -5.983133;0.750000;,
    -5.983133;1.000000;,
    -5.983133;1.000000;,
    -5.983133;0.750000;,
    6.983133;0.100000;,
    6.983133;0.100000;,
    6.983133;0.750000;,
    6.983133;1.000000;,
    6.983133;0.750000;,
    6.983133;1.000000;,
    -5.983133;0.100000;,
    -5.983133;0.100000;,
    -5.983133;0.100000;,
    -5.983133;0.750000;,
    6.983133;0.100000;,
    6.983133;0.100000;,
    6.983133;0.100000;,
    6.983133;0.750000;,
    6.983133;0.750000;,
    6.983133;1.000000;,
    -5.983133;1.000000;,
    -5.983133;0.750000;,
    6.983133;1.000000;,
    6.983133;1.000000;,
    -5.983133;1.000000;,
    -5.983133;1.000000;,
    -5.983133;1.000000;,
    6.983133;1.000000;,
    6.983133;0.750000;,
    -5.983133;0.750000;,
    6.983133;0.750000;,
    -5.983133;0.750000;,
    -5.983133;0.100000;,
    6.983133;0.100000;;
   }

   MeshMaterialList {
    1;
    8;
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
      "cementmedian2.bmp";
     }
    }
   }

   VertexDuplicationIndices {
    36;
    12;
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
    1,
    0,
    0,
    5,
    6,
    7,
    6,
    8,
    10,
    9,
    3,
    2,
    9,
    11,
    4,
    3,
    4,
    11,
    8,
    5,
    10,
    2,
    1,
    7;
   }
  }
 }
}

AnimationSet {
 
}