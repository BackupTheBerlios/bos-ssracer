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
   0.999945,0.000000,0.010472,0.000000,0.010421,0.098654,-0.995067,0.000000,-0.001033,0.995122,0.098648,0.000000,21.600792,335.848114,82.069527,1.000000;;
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
   374;
   -50.000000;19.995001;50.000000;,
   -40.000000;19.995001;50.000000;,
   -40.000000;19.995001;40.000000;,
   -50.000000;19.995001;40.000000;,
   -30.000002;19.995001;50.000000;,
   -30.000002;19.995001;40.000000;,
   -19.999998;19.995001;50.000000;,
   -19.999998;19.995001;40.000000;,
   -9.999999;19.995001;50.000000;,
   -9.999999;19.995001;40.000000;,
   0.000001;19.995001;50.000000;,
   0.000001;19.995001;40.000000;,
   10.000001;19.995001;50.000000;,
   10.000001;19.995001;40.000000;,
   20.000002;19.995001;50.000000;,
   20.000002;19.995001;40.000000;,
   30.000002;19.995001;50.000000;,
   30.000002;19.995001;40.000000;,
   40.000000;19.995001;50.000000;,
   40.000000;19.995001;40.000000;,
   50.000000;19.995001;50.000000;,
   50.000000;19.995001;40.000000;,
   -40.000000;19.995001;30.000002;,
   -50.000000;19.995001;30.000002;,
   -30.000002;19.995001;30.000002;,
   -19.999998;19.995001;30.000002;,
   -9.999999;19.995001;30.000002;,
   0.000001;19.995001;30.000002;,
   10.000001;19.995001;30.000002;,
   20.000002;19.995001;30.000002;,
   30.000002;19.995001;30.000002;,
   40.000000;19.995001;30.000002;,
   50.000000;19.995001;30.000002;,
   -40.000000;19.995001;19.999998;,
   -50.000000;19.995001;19.999998;,
   -30.000002;19.995001;19.999998;,
   -19.999998;19.995001;19.999998;,
   -9.999999;19.995001;19.999998;,
   0.000001;19.995001;19.999998;,
   10.000001;19.995001;19.999998;,
   20.000002;19.995001;19.999998;,
   30.000002;19.995001;19.999998;,
   40.000000;19.995001;19.999998;,
   50.000000;19.995001;19.999998;,
   -40.000000;19.995001;9.999999;,
   -50.000000;19.995001;9.999999;,
   -30.000002;19.995001;9.999999;,
   -19.999998;19.995001;9.999999;,
   -9.999999;19.995001;9.999999;,
   0.000001;19.995001;9.999999;,
   10.000001;19.995001;9.999999;,
   20.000002;19.995001;9.999999;,
   30.000002;19.995001;9.999999;,
   40.000000;19.995001;9.999999;,
   50.000000;19.995001;9.999999;,
   -40.000000;19.995001;-0.000001;,
   -50.000000;19.995001;-0.000001;,
   -30.000002;19.995001;-0.000001;,
   -19.999998;19.995001;-0.000001;,
   -9.999999;19.995001;-0.000001;,
   0.000001;19.995001;-0.000001;,
   10.000001;19.995001;-0.000001;,
   20.000002;19.995001;-0.000001;,
   30.000002;19.995001;-0.000001;,
   40.000000;19.995001;-0.000001;,
   50.000000;19.995001;-0.000001;,
   -40.000000;19.995001;-10.000001;,
   -50.000000;19.995001;-10.000001;,
   -30.000002;19.995001;-10.000001;,
   -19.999998;19.995001;-10.000001;,
   -9.999999;19.995001;-10.000001;,
   0.000001;19.995001;-10.000001;,
   10.000001;19.995001;-10.000001;,
   20.000002;19.995001;-10.000001;,
   30.000002;19.995001;-10.000001;,
   40.000000;19.995001;-10.000001;,
   50.000000;19.995001;-10.000001;,
   -40.000000;19.995001;-20.000002;,
   -50.000000;19.995001;-20.000002;,
   -30.000002;19.995001;-20.000002;,
   -19.999998;19.995001;-20.000002;,
   -9.999999;19.995001;-20.000002;,
   0.000001;19.995001;-20.000002;,
   10.000001;19.995001;-20.000002;,
   20.000002;19.995001;-20.000002;,
   30.000002;19.995001;-20.000002;,
   40.000000;19.995001;-20.000002;,
   50.000000;19.995001;-20.000002;,
   -40.000000;19.995001;-30.000002;,
   -50.000000;19.995001;-30.000002;,
   -30.000002;19.995001;-30.000002;,
   -19.999998;19.995001;-30.000002;,
   -9.999999;19.995001;-30.000002;,
   0.000001;19.995001;-30.000002;,
   10.000001;19.995001;-30.000002;,
   20.000002;19.995001;-30.000002;,
   30.000002;19.995001;-30.000002;,
   40.000000;19.995001;-30.000002;,
   50.000000;19.995001;-30.000002;,
   -40.000000;19.995001;-40.000000;,
   -50.000000;19.995001;-40.000000;,
   -30.000002;19.995001;-40.000000;,
   -19.999998;19.995001;-40.000000;,
   -9.999999;19.995001;-40.000000;,
   0.000001;19.995001;-40.000000;,
   10.000001;19.995001;-40.000000;,
   20.000002;19.995001;-40.000000;,
   30.000002;19.995001;-40.000000;,
   40.000000;19.995001;-40.000000;,
   50.000000;19.995001;-40.000000;,
   -40.000000;19.995001;-50.000000;,
   -50.000000;19.995001;-50.000000;,
   -30.000002;19.995001;-50.000000;,
   -19.999998;19.995001;-50.000000;,
   -9.999999;19.995001;-50.000000;,
   0.000001;19.995001;-50.000000;,
   10.000001;19.995001;-50.000000;,
   20.000002;19.995001;-50.000000;,
   30.000002;19.995001;-50.000000;,
   40.000000;19.995001;-50.000000;,
   50.000000;17.995001;-50.000000;,
   -40.000000;19.995001;50.000000;,
   -40.000000;19.995001;40.000000;,
   -30.000002;19.995001;50.000000;,
   -30.000002;19.995001;40.000000;,
   -19.999998;19.995001;50.000000;,
   -19.999998;19.995001;40.000000;,
   -9.999999;19.995001;50.000000;,
   -9.999999;19.995001;40.000000;,
   0.000001;19.995001;50.000000;,
   0.000001;19.995001;40.000000;,
   10.000001;19.995001;50.000000;,
   10.000001;19.995001;40.000000;,
   20.000002;19.995001;50.000000;,
   20.000002;19.995001;40.000000;,
   30.000002;19.995001;50.000000;,
   30.000002;19.995001;40.000000;,
   40.000000;19.995001;50.000000;,
   40.000000;19.995001;40.000000;,
   -50.000000;19.995001;40.000000;,
   -40.000000;19.995001;40.000000;,
   -40.000000;19.995001;40.000000;,
   -30.000002;19.995001;40.000000;,
   -40.000000;19.995001;30.000002;,
   -30.000002;19.995001;40.000000;,
   -19.999998;19.995001;40.000000;,
   -30.000002;19.995001;30.000002;,
   -19.999998;19.995001;40.000000;,
   -9.999999;19.995001;40.000000;,
   -19.999998;19.995001;30.000002;,
   -9.999999;19.995001;40.000000;,
   0.000001;19.995001;40.000000;,
   -9.999999;19.995001;30.000002;,
   0.000001;19.995001;40.000000;,
   10.000001;19.995001;40.000000;,
   0.000001;19.995001;30.000002;,
   10.000001;19.995001;40.000000;,
   20.000002;19.995001;40.000000;,
   10.000001;19.995001;30.000002;,
   20.000002;19.995001;40.000000;,
   30.000002;19.995001;40.000000;,
   20.000002;19.995001;30.000002;,
   30.000002;19.995001;40.000000;,
   40.000000;19.995001;40.000000;,
   30.000002;19.995001;30.000002;,
   40.000000;19.995001;40.000000;,
   50.000000;19.995001;40.000000;,
   40.000000;19.995001;30.000002;,
   -50.000000;19.995001;30.000002;,
   -40.000000;19.995001;30.000002;,
   -40.000000;19.995001;30.000002;,
   -30.000002;19.995001;30.000002;,
   -40.000000;19.995001;19.999998;,
   -30.000002;19.995001;30.000002;,
   -19.999998;19.995001;30.000002;,
   -30.000002;19.995001;19.999998;,
   -19.999998;19.995001;30.000002;,
   -9.999999;19.995001;30.000002;,
   -19.999998;19.995001;19.999998;,
   -9.999999;19.995001;30.000002;,
   0.000001;19.995001;30.000002;,
   -9.999999;19.995001;19.999998;,
   0.000001;19.995001;30.000002;,
   10.000001;19.995001;30.000002;,
   0.000001;19.995001;19.999998;,
   10.000001;19.995001;30.000002;,
   20.000002;19.995001;30.000002;,
   10.000001;19.995001;19.999998;,
   20.000002;19.995001;30.000002;,
   30.000002;19.995001;30.000002;,
   20.000002;19.995001;19.999998;,
   30.000002;19.995001;30.000002;,
   40.000000;19.995001;30.000002;,
   30.000002;19.995001;19.999998;,
   40.000000;19.995001;30.000002;,
   50.000000;19.995001;30.000002;,
   40.000000;19.995001;19.999998;,
   -50.000000;19.995001;19.999998;,
   -40.000000;19.995001;19.999998;,
   -40.000000;19.995001;19.999998;,
   -30.000002;19.995001;19.999998;,
   -40.000000;19.995001;9.999999;,
   -30.000002;19.995001;19.999998;,
   -19.999998;19.995001;19.999998;,
   -30.000002;19.995001;9.999999;,
   -19.999998;19.995001;19.999998;,
   -9.999999;19.995001;19.999998;,
   -19.999998;19.995001;9.999999;,
   -9.999999;19.995001;19.999998;,
   0.000001;19.995001;19.999998;,
   -9.999999;19.995001;9.999999;,
   0.000001;19.995001;19.999998;,
   10.000001;19.995001;19.999998;,
   0.000001;19.995001;9.999999;,
   10.000001;19.995001;19.999998;,
   20.000002;19.995001;19.999998;,
   10.000001;19.995001;9.999999;,
   20.000002;19.995001;19.999998;,
   30.000002;19.995001;19.999998;,
   20.000002;19.995001;9.999999;,
   30.000002;19.995001;19.999998;,
   40.000000;19.995001;19.999998;,
   30.000002;19.995001;9.999999;,
   40.000000;19.995001;19.999998;,
   50.000000;19.995001;19.999998;,
   40.000000;19.995001;9.999999;,
   -50.000000;19.995001;9.999999;,
   -40.000000;19.995001;9.999999;,
   -40.000000;19.995001;9.999999;,
   -30.000002;19.995001;9.999999;,
   -40.000000;19.995001;-0.000001;,
   -30.000002;19.995001;9.999999;,
   -19.999998;19.995001;9.999999;,
   -30.000002;19.995001;-0.000001;,
   -19.999998;19.995001;9.999999;,
   -9.999999;19.995001;9.999999;,
   -19.999998;19.995001;-0.000001;,
   -9.999999;19.995001;9.999999;,
   0.000001;19.995001;9.999999;,
   -9.999999;19.995001;-0.000001;,
   0.000001;19.995001;9.999999;,
   10.000001;19.995001;9.999999;,
   0.000001;19.995001;-0.000001;,
   10.000001;19.995001;9.999999;,
   20.000002;19.995001;9.999999;,
   10.000001;19.995001;-0.000001;,
   20.000002;19.995001;9.999999;,
   30.000002;19.995001;9.999999;,
   20.000002;19.995001;-0.000001;,
   30.000002;19.995001;-0.000001;,
   40.000000;19.995001;9.999999;,
   50.000000;19.995001;9.999999;,
   40.000000;19.995001;-0.000001;,
   -40.000000;19.995001;-10.000001;,
   -30.000002;19.995001;-0.000001;,
   -19.999998;19.995001;-0.000001;,
   -30.000002;19.995001;-10.000001;,
   -19.999998;19.995001;-10.000001;,
   -9.999999;19.995001;-10.000001;,
   0.000001;19.995001;-10.000001;,
   10.000001;19.995001;-10.000001;,
   20.000002;19.995001;-10.000001;,
   30.000002;19.995001;-0.000001;,
   40.000000;19.995001;-0.000001;,
   30.000002;19.995001;-10.000001;,
   40.000000;19.995001;-10.000001;,
   -50.000000;19.995001;-10.000001;,
   -40.000000;19.995001;-10.000001;,
   -40.000000;19.995001;-20.000002;,
   -30.000002;19.995001;-10.000001;,
   -19.999998;19.995001;-10.000001;,
   -30.000002;19.995001;-20.000002;,
   -19.999998;19.995001;-10.000001;,
   -9.999999;19.995001;-10.000001;,
   -19.999998;19.995001;-20.000002;,
   -9.999999;19.995001;-10.000001;,
   0.000001;19.995001;-10.000001;,
   -9.999999;19.995001;-20.000002;,
   0.000001;19.995001;-10.000001;,
   10.000001;19.995001;-10.000001;,
   0.000001;19.995001;-20.000002;,
   10.000001;19.995001;-10.000001;,
   20.000002;19.995001;-10.000001;,
   10.000001;19.995001;-20.000002;,
   20.000002;19.995001;-10.000001;,
   30.000002;19.995001;-10.000001;,
   20.000002;19.995001;-20.000002;,
   30.000002;19.995001;-20.000002;,
   40.000000;19.995001;-10.000001;,
   50.000000;19.995001;-10.000001;,
   40.000000;19.995001;-20.000002;,
   -50.000000;19.995001;-20.000002;,
   -40.000000;19.995001;-20.000002;,
   -40.000000;19.995001;-30.000002;,
   -30.000002;19.995001;-20.000002;,
   -19.999998;19.995001;-20.000002;,
   -30.000002;19.995001;-30.000002;,
   -19.999998;19.995001;-20.000002;,
   -9.999999;19.995001;-20.000002;,
   -19.999998;19.995001;-30.000002;,
   -9.999999;19.995001;-20.000002;,
   0.000001;19.995001;-20.000002;,
   -9.999999;19.995001;-30.000002;,
   0.000001;19.995001;-20.000002;,
   10.000001;19.995001;-20.000002;,
   0.000001;19.995001;-30.000002;,
   10.000001;19.995001;-20.000002;,
   20.000002;19.995001;-20.000002;,
   10.000001;19.995001;-30.000002;,
   20.000002;19.995001;-20.000002;,
   30.000002;19.995001;-20.000002;,
   20.000002;19.995001;-30.000002;,
   30.000002;19.995001;-30.000002;,
   40.000000;19.995001;-20.000002;,
   50.000000;19.995001;-20.000002;,
   40.000000;19.995001;-30.000002;,
   -50.000000;19.995001;-30.000002;,
   -40.000000;19.995001;-30.000002;,
   -40.000000;19.995001;-30.000002;,
   -30.000002;19.995001;-30.000002;,
   -40.000000;19.995001;-40.000000;,
   -30.000002;19.995001;-30.000002;,
   -19.999998;19.995001;-30.000002;,
   -30.000002;19.995001;-40.000000;,
   -19.999998;19.995001;-30.000002;,
   -9.999999;19.995001;-30.000002;,
   -19.999998;19.995001;-40.000000;,
   -9.999999;19.995001;-30.000002;,
   0.000001;19.995001;-30.000002;,
   -9.999999;19.995001;-40.000000;,
   0.000001;19.995001;-30.000002;,
   10.000001;19.995001;-30.000002;,
   0.000001;19.995001;-40.000000;,
   10.000001;19.995001;-30.000002;,
   20.000002;19.995001;-30.000002;,
   10.000001;19.995001;-40.000000;,
   20.000002;19.995001;-30.000002;,
   30.000002;19.995001;-30.000002;,
   20.000002;19.995001;-40.000000;,
   30.000002;19.995001;-30.000002;,
   40.000000;19.995001;-30.000002;,
   30.000002;19.995001;-40.000000;,
   40.000000;19.995001;-30.000002;,
   50.000000;19.995001;-30.000002;,
   40.000000;19.995001;-40.000000;,
   -50.000000;19.995001;-40.000000;,
   -40.000000;19.995001;-40.000000;,
   -40.000000;19.995001;-40.000000;,
   -30.000002;19.995001;-40.000000;,
   -40.000000;19.995001;-50.000000;,
   -30.000002;19.995001;-40.000000;,
   -19.999998;19.995001;-40.000000;,
   -30.000002;19.995001;-50.000000;,
   -19.999998;19.995001;-40.000000;,
   -9.999999;19.995001;-40.000000;,
   -19.999998;19.995001;-50.000000;,
   -9.999999;19.995001;-40.000000;,
   0.000001;19.995001;-40.000000;,
   -9.999999;19.995001;-50.000000;,
   0.000001;19.995001;-40.000000;,
   10.000001;19.995001;-40.000000;,
   0.000001;19.995001;-50.000000;,
   10.000001;19.995001;-40.000000;,
   20.000002;19.995001;-40.000000;,
   10.000001;19.995001;-50.000000;,
   20.000002;19.995001;-40.000000;,
   30.000002;19.995001;-40.000000;,
   20.000002;19.995001;-50.000000;,
   30.000002;19.995001;-40.000000;,
   40.000000;19.995001;-40.000000;,
   30.000002;19.995001;-50.000000;,
   40.000000;19.995001;-40.000000;,
   50.000000;19.995001;-40.000000;,
   40.000000;19.995001;-50.000000;;
   100;
   4;3,2,1,0;,
   4;122,5,4,121;,
   4;124,7,6,123;,
   4;126,9,8,125;,
   4;128,11,10,127;,
   4;130,13,12,129;,
   4;132,15,14,131;,
   4;134,17,16,133;,
   4;136,19,18,135;,
   4;138,21,20,137;,
   4;23,22,140,139;,
   4;143,24,142,141;,
   4;146,25,145,144;,
   4;149,26,148,147;,
   4;152,27,151,150;,
   4;155,28,154,153;,
   4;158,29,157,156;,
   4;161,30,160,159;,
   4;164,31,163,162;,
   4;167,32,166,165;,
   4;34,33,169,168;,
   4;172,35,171,170;,
   4;175,36,174,173;,
   4;178,37,177,176;,
   4;181,38,180,179;,
   4;184,39,183,182;,
   4;187,40,186,185;,
   4;190,41,189,188;,
   4;193,42,192,191;,
   4;196,43,195,194;,
   4;45,44,198,197;,
   4;201,46,200,199;,
   4;204,47,203,202;,
   4;207,48,206,205;,
   4;210,49,209,208;,
   4;213,50,212,211;,
   4;216,51,215,214;,
   4;219,52,218,217;,
   4;222,53,221,220;,
   4;225,54,224,223;,
   4;56,55,227,226;,
   4;230,57,229,228;,
   4;233,58,232,231;,
   4;236,59,235,234;,
   4;239,60,238,237;,
   4;242,61,241,240;,
   4;245,62,244,243;,
   4;248,63,247,246;,
   4;249,64,53,222;,
   4;252,65,251,250;,
   4;67,66,55,56;,
   4;253,68,57,230;,
   4;256,69,255,254;,
   4;257,70,59,236;,
   4;258,71,60,239;,
   4;259,72,61,242;,
   4;260,73,62,245;,
   4;261,74,63,248;,
   4;264,75,263,262;,
   4;265,76,65,252;,
   4;78,77,267,266;,
   4;268,79,68,253;,
   4;271,80,270,269;,
   4;274,81,273,272;,
   4;277,82,276,275;,
   4;280,83,279,278;,
   4;283,84,282,281;,
   4;286,85,285,284;,
   4;287,86,75,264;,
   4;290,87,289,288;,
   4;89,88,292,291;,
   4;293,90,79,268;,
   4;296,91,295,294;,
   4;299,92,298,297;,
   4;302,93,301,300;,
   4;305,94,304,303;,
   4;308,95,307,306;,
   4;311,96,310,309;,
   4;312,97,86,287;,
   4;315,98,314,313;,
   4;100,99,317,316;,
   4;320,101,319,318;,
   4;323,102,322,321;,
   4;326,103,325,324;,
   4;329,104,328,327;,
   4;332,105,331,330;,
   4;335,106,334,333;,
   4;338,107,337,336;,
   4;341,108,340,339;,
   4;344,109,343,342;,
   4;111,110,346,345;,
   4;349,112,348,347;,
   4;352,113,351,350;,
   4;355,114,354,353;,
   4;358,115,357,356;,
   4;361,116,360,359;,
   4;364,117,363,362;,
   4;367,118,366,365;,
   4;370,119,369,368;,
   4;373,120,372,371;;

   MeshNormals {
    38;
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
    0.000000;1.000000;-0.000000;,
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
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    0.099015;0.990148;-0.099015;;
    100;
    4;16,16,16,16;,
    4;34,34,34,34;,
    4;10,10,10,10;,
    4;1,1,1,1;,
    4;23,23,23,23;,
    4;6,6,6,6;,
    4;28,28,28,28;,
    4;17,17,17,17;,
    4;33,33,33,33;,
    4;16,16,16,16;,
    4;13,13,13,13;,
    4;36,36,36,36;,
    4;9,9,9,9;,
    4;0,0,0,0;,
    4;21,21,21,21;,
    4;4,4,4,4;,
    4;26,26,26,26;,
    4;15,15,15,15;,
    4;34,34,34,34;,
    4;14,14,14,14;,
    4;20,20,20,20;,
    4;31,31,31,31;,
    4;12,12,12,12;,
    4;3,3,3,3;,
    4;25,25,25,25;,
    4;8,8,8,8;,
    4;30,30,30,30;,
    4;18,18,18,18;,
    4;32,32,32,32;,
    4;19,19,19,19;,
    4;14,14,14,14;,
    4;35,35,35,35;,
    4;9,9,9,9;,
    4;0,0,0,0;,
    4;22,22,22,22;,
    4;5,5,5,5;,
    4;27,27,27,27;,
    4;16,16,16,16;,
    4;34,34,34,34;,
    4;13,13,13,13;,
    4;16,16,16,16;,
    4;34,34,34,34;,
    4;11,11,11,11;,
    4;1,1,1,1;,
    4;23,23,23,23;,
    4;6,6,6,6;,
    4;28,28,28,28;,
    4;17,17,17,17;,
    4;34,34,34,34;,
    4;16,16,16,16;,
    4;16,16,16,16;,
    4;34,34,34,34;,
    4;10,10,10,10;,
    4;1,1,1,1;,
    4;23,23,23,23;,
    4;6,6,6,6;,
    4;28,28,28,28;,
    4;17,17,17,17;,
    4;33,33,33,33;,
    4;16,16,16,16;,
    4;17,17,17,17;,
    4;34,34,34,34;,
    4;11,11,11,11;,
    4;2,2,2,2;,
    4;24,24,24,24;,
    4;7,7,7,7;,
    4;29,29,29,29;,
    4;18,18,18,18;,
    4;33,33,33,33;,
    4;18,18,18,18;,
    4;16,16,16,16;,
    4;34,34,34,34;,
    4;10,10,10,10;,
    4;1,1,1,1;,
    4;23,23,23,23;,
    4;6,6,6,6;,
    4;28,28,28,28;,
    4;17,17,17,17;,
    4;33,33,33,33;,
    4;16,16,16,16;,
    4;13,13,13,13;,
    4;36,36,36,36;,
    4;9,9,9,9;,
    4;0,0,0,0;,
    4;21,21,21,21;,
    4;4,4,4,4;,
    4;26,26,26,26;,
    4;15,15,15,15;,
    4;34,34,34,34;,
    4;14,14,14,14;,
    4;16,16,16,16;,
    4;34,34,34,34;,
    4;10,10,10,10;,
    4;1,1,1,1;,
    4;23,23,23,23;,
    4;6,6,6,6;,
    4;28,28,28,28;,
    4;17,17,17,17;,
    4;33,33,33,33;,
    4;37,37,37,37;;
   }

   MeshTextureCoords {
    374;
    0.000000;1.000000;,
    0.100000;1.000000;,
    0.100000;0.900000;,
    0.000000;0.900000;,
    0.200000;1.000000;,
    0.200000;0.900000;,
    0.300000;1.000000;,
    0.300000;0.900000;,
    0.400000;1.000000;,
    0.400000;0.900000;,
    0.500000;1.000000;,
    0.500000;0.900000;,
    0.600000;1.000000;,
    0.600000;0.900000;,
    0.700000;1.000000;,
    0.700000;0.900000;,
    0.800000;1.000000;,
    0.800000;0.900000;,
    0.900000;1.000000;,
    0.900000;0.900000;,
    1.000000;1.000000;,
    1.000000;0.900000;,
    0.100000;0.800000;,
    0.000000;0.800000;,
    0.200000;0.800000;,
    0.300000;0.800000;,
    0.400000;0.800000;,
    0.500000;0.800000;,
    0.600000;0.800000;,
    0.700000;0.800000;,
    0.800000;0.800000;,
    0.900000;0.800000;,
    1.000000;0.800000;,
    0.100000;0.700000;,
    0.000000;0.700000;,
    0.200000;0.700000;,
    0.300000;0.700000;,
    0.400000;0.700000;,
    0.500000;0.700000;,
    0.600000;0.700000;,
    0.700000;0.700000;,
    0.800000;0.700000;,
    0.900000;0.700000;,
    1.000000;0.700000;,
    0.100000;0.600000;,
    0.000000;0.600000;,
    0.200000;0.600000;,
    0.300000;0.600000;,
    0.400000;0.600000;,
    0.500000;0.600000;,
    0.600000;0.600000;,
    0.700000;0.600000;,
    0.800000;0.600000;,
    0.900000;0.600000;,
    1.000000;0.600000;,
    0.100000;0.500000;,
    0.000000;0.500000;,
    0.200000;0.500000;,
    0.300000;0.500000;,
    0.400000;0.500000;,
    0.500000;0.500000;,
    0.600000;0.500000;,
    0.700000;0.500000;,
    0.800000;0.500000;,
    0.900000;0.500000;,
    1.000000;0.500000;,
    0.100000;0.400000;,
    0.000000;0.400000;,
    0.200000;0.400000;,
    0.300000;0.400000;,
    0.400000;0.400000;,
    0.500000;0.400000;,
    0.600000;0.400000;,
    0.700000;0.400000;,
    0.800000;0.400000;,
    0.900000;0.400000;,
    1.000000;0.400000;,
    0.100000;0.300000;,
    0.000000;0.300000;,
    0.200000;0.300000;,
    0.300000;0.300000;,
    0.400000;0.300000;,
    0.500000;0.300000;,
    0.600000;0.300000;,
    0.700000;0.300000;,
    0.800000;0.300000;,
    0.900000;0.300000;,
    1.000000;0.300000;,
    0.100000;0.200000;,
    0.000000;0.200000;,
    0.200000;0.200000;,
    0.300000;0.200000;,
    0.400000;0.200000;,
    0.500000;0.200000;,
    0.600000;0.200000;,
    0.700000;0.200000;,
    0.800000;0.200000;,
    0.900000;0.200000;,
    1.000000;0.200000;,
    0.100000;0.100000;,
    0.000000;0.100000;,
    0.200000;0.100000;,
    0.300000;0.100000;,
    0.400000;0.100000;,
    0.500000;0.100000;,
    0.600000;0.100000;,
    0.700000;0.100000;,
    0.800000;0.100000;,
    0.900000;0.100000;,
    1.000000;0.100000;,
    0.100000;0.000000;,
    0.000000;0.000000;,
    0.200000;0.000000;,
    0.300000;0.000000;,
    0.400000;0.000000;,
    0.500000;0.000000;,
    0.600000;0.000000;,
    0.700000;0.000000;,
    0.800000;0.000000;,
    0.900000;0.000000;,
    1.000000;0.000000;,
    0.100000;1.000000;,
    0.100000;0.900000;,
    0.200000;1.000000;,
    0.200000;0.900000;,
    0.300000;1.000000;,
    0.300000;0.900000;,
    0.400000;1.000000;,
    0.400000;0.900000;,
    0.500000;1.000000;,
    0.500000;0.900000;,
    0.600000;1.000000;,
    0.600000;0.900000;,
    0.700000;1.000000;,
    0.700000;0.900000;,
    0.800000;1.000000;,
    0.800000;0.900000;,
    0.900000;1.000000;,
    0.900000;0.900000;,
    0.000000;0.900000;,
    0.100000;0.900000;,
    0.100000;0.900000;,
    0.200000;0.900000;,
    0.100000;0.800000;,
    0.200000;0.900000;,
    0.300000;0.900000;,
    0.200000;0.800000;,
    0.300000;0.900000;,
    0.400000;0.900000;,
    0.300000;0.800000;,
    0.400000;0.900000;,
    0.500000;0.900000;,
    0.400000;0.800000;,
    0.500000;0.900000;,
    0.600000;0.900000;,
    0.500000;0.800000;,
    0.600000;0.900000;,
    0.700000;0.900000;,
    0.600000;0.800000;,
    0.700000;0.900000;,
    0.800000;0.900000;,
    0.700000;0.800000;,
    0.800000;0.900000;,
    0.900000;0.900000;,
    0.800000;0.800000;,
    0.900000;0.900000;,
    1.000000;0.900000;,
    0.900000;0.800000;,
    0.000000;0.800000;,
    0.100000;0.800000;,
    0.100000;0.800000;,
    0.200000;0.800000;,
    0.100000;0.700000;,
    0.200000;0.800000;,
    0.300000;0.800000;,
    0.200000;0.700000;,
    0.300000;0.800000;,
    0.400000;0.800000;,
    0.300000;0.700000;,
    0.400000;0.800000;,
    0.500000;0.800000;,
    0.400000;0.700000;,
    0.500000;0.800000;,
    0.600000;0.800000;,
    0.500000;0.700000;,
    0.600000;0.800000;,
    0.700000;0.800000;,
    0.600000;0.700000;,
    0.700000;0.800000;,
    0.800000;0.800000;,
    0.700000;0.700000;,
    0.800000;0.800000;,
    0.900000;0.800000;,
    0.800000;0.700000;,
    0.900000;0.800000;,
    1.000000;0.800000;,
    0.900000;0.700000;,
    0.000000;0.700000;,
    0.100000;0.700000;,
    0.100000;0.700000;,
    0.200000;0.700000;,
    0.100000;0.600000;,
    0.200000;0.700000;,
    0.300000;0.700000;,
    0.200000;0.600000;,
    0.300000;0.700000;,
    0.400000;0.700000;,
    0.300000;0.600000;,
    0.400000;0.700000;,
    0.500000;0.700000;,
    0.400000;0.600000;,
    0.500000;0.700000;,
    0.600000;0.700000;,
    0.500000;0.600000;,
    0.600000;0.700000;,
    0.700000;0.700000;,
    0.600000;0.600000;,
    0.700000;0.700000;,
    0.800000;0.700000;,
    0.700000;0.600000;,
    0.800000;0.700000;,
    0.900000;0.700000;,
    0.800000;0.600000;,
    0.900000;0.700000;,
    1.000000;0.700000;,
    0.900000;0.600000;,
    0.000000;0.600000;,
    0.100000;0.600000;,
    0.100000;0.600000;,
    0.200000;0.600000;,
    0.100000;0.500000;,
    0.200000;0.600000;,
    0.300000;0.600000;,
    0.200000;0.500000;,
    0.300000;0.600000;,
    0.400000;0.600000;,
    0.300000;0.500000;,
    0.400000;0.600000;,
    0.500000;0.600000;,
    0.400000;0.500000;,
    0.500000;0.600000;,
    0.600000;0.600000;,
    0.500000;0.500000;,
    0.600000;0.600000;,
    0.700000;0.600000;,
    0.600000;0.500000;,
    0.700000;0.600000;,
    0.800000;0.600000;,
    0.700000;0.500000;,
    0.800000;0.500000;,
    0.900000;0.600000;,
    1.000000;0.600000;,
    0.900000;0.500000;,
    0.100000;0.400000;,
    0.200000;0.500000;,
    0.300000;0.500000;,
    0.200000;0.400000;,
    0.300000;0.400000;,
    0.400000;0.400000;,
    0.500000;0.400000;,
    0.600000;0.400000;,
    0.700000;0.400000;,
    0.800000;0.500000;,
    0.900000;0.500000;,
    0.800000;0.400000;,
    0.900000;0.400000;,
    0.000000;0.400000;,
    0.100000;0.400000;,
    0.100000;0.300000;,
    0.200000;0.400000;,
    0.300000;0.400000;,
    0.200000;0.300000;,
    0.300000;0.400000;,
    0.400000;0.400000;,
    0.300000;0.300000;,
    0.400000;0.400000;,
    0.500000;0.400000;,
    0.400000;0.300000;,
    0.500000;0.400000;,
    0.600000;0.400000;,
    0.500000;0.300000;,
    0.600000;0.400000;,
    0.700000;0.400000;,
    0.600000;0.300000;,
    0.700000;0.400000;,
    0.800000;0.400000;,
    0.700000;0.300000;,
    0.800000;0.300000;,
    0.900000;0.400000;,
    1.000000;0.400000;,
    0.900000;0.300000;,
    0.000000;0.300000;,
    0.100000;0.300000;,
    0.100000;0.200000;,
    0.200000;0.300000;,
    0.300000;0.300000;,
    0.200000;0.200000;,
    0.300000;0.300000;,
    0.400000;0.300000;,
    0.300000;0.200000;,
    0.400000;0.300000;,
    0.500000;0.300000;,
    0.400000;0.200000;,
    0.500000;0.300000;,
    0.600000;0.300000;,
    0.500000;0.200000;,
    0.600000;0.300000;,
    0.700000;0.300000;,
    0.600000;0.200000;,
    0.700000;0.300000;,
    0.800000;0.300000;,
    0.700000;0.200000;,
    0.800000;0.200000;,
    0.900000;0.300000;,
    1.000000;0.300000;,
    0.900000;0.200000;,
    0.000000;0.200000;,
    0.100000;0.200000;,
    0.100000;0.200000;,
    0.200000;0.200000;,
    0.100000;0.100000;,
    0.200000;0.200000;,
    0.300000;0.200000;,
    0.200000;0.100000;,
    0.300000;0.200000;,
    0.400000;0.200000;,
    0.300000;0.100000;,
    0.400000;0.200000;,
    0.500000;0.200000;,
    0.400000;0.100000;,
    0.500000;0.200000;,
    0.600000;0.200000;,
    0.500000;0.100000;,
    0.600000;0.200000;,
    0.700000;0.200000;,
    0.600000;0.100000;,
    0.700000;0.200000;,
    0.800000;0.200000;,
    0.700000;0.100000;,
    0.800000;0.200000;,
    0.900000;0.200000;,
    0.800000;0.100000;,
    0.900000;0.200000;,
    1.000000;0.200000;,
    0.900000;0.100000;,
    0.000000;0.100000;,
    0.100000;0.100000;,
    0.100000;0.100000;,
    0.200000;0.100000;,
    0.100000;0.000000;,
    0.200000;0.100000;,
    0.300000;0.100000;,
    0.200000;0.000000;,
    0.300000;0.100000;,
    0.400000;0.100000;,
    0.300000;0.000000;,
    0.400000;0.100000;,
    0.500000;0.100000;,
    0.400000;0.000000;,
    0.500000;0.100000;,
    0.600000;0.100000;,
    0.500000;0.000000;,
    0.600000;0.100000;,
    0.700000;0.100000;,
    0.600000;0.000000;,
    0.700000;0.100000;,
    0.800000;0.100000;,
    0.700000;0.000000;,
    0.800000;0.100000;,
    0.900000;0.100000;,
    0.800000;0.000000;,
    0.900000;0.100000;,
    1.000000;0.100000;,
    0.900000;0.000000;;
   }

   MeshMaterialList {
    1;
    100;
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
    0,
    0;

    Material lambert2SG {
     0.800000;0.800000;0.800000;1.000000;;
     0.000000;
     0.000000;0.000000;0.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "grass_small.bmp";
     }
    }
   }

   VertexDuplicationIndices {
    374;
    121;
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
    66,
    67,
    68,
    69,
    70,
    71,
    72,
    73,
    74,
    75,
    76,
    77,
    78,
    79,
    80,
    81,
    82,
    83,
    84,
    85,
    86,
    87,
    88,
    89,
    90,
    91,
    92,
    93,
    94,
    95,
    96,
    97,
    98,
    99,
    100,
    101,
    102,
    103,
    104,
    105,
    106,
    107,
    108,
    109,
    110,
    111,
    112,
    113,
    114,
    115,
    116,
    117,
    118,
    119,
    120,
    1,
    2,
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
    3,
    2,
    2,
    5,
    22,
    5,
    7,
    24,
    7,
    9,
    25,
    9,
    11,
    26,
    11,
    13,
    27,
    13,
    15,
    28,
    15,
    17,
    29,
    17,
    19,
    30,
    19,
    21,
    31,
    23,
    22,
    22,
    24,
    33,
    24,
    25,
    35,
    25,
    26,
    36,
    26,
    27,
    37,
    27,
    28,
    38,
    28,
    29,
    39,
    29,
    30,
    40,
    30,
    31,
    41,
    31,
    32,
    42,
    34,
    33,
    33,
    35,
    44,
    35,
    36,
    46,
    36,
    37,
    47,
    37,
    38,
    48,
    38,
    39,
    49,
    39,
    40,
    50,
    40,
    41,
    51,
    41,
    42,
    52,
    42,
    43,
    53,
    45,
    44,
    44,
    46,
    55,
    46,
    47,
    57,
    47,
    48,
    58,
    48,
    49,
    59,
    49,
    50,
    60,
    50,
    51,
    61,
    51,
    52,
    62,
    63,
    53,
    54,
    64,
    66,
    57,
    58,
    68,
    69,
    70,
    71,
    72,
    73,
    63,
    64,
    74,
    75,
    67,
    66,
    77,
    68,
    69,
    79,
    69,
    70,
    80,
    70,
    71,
    81,
    71,
    72,
    82,
    72,
    73,
    83,
    73,
    74,
    84,
    85,
    75,
    76,
    86,
    78,
    77,
    88,
    79,
    80,
    90,
    80,
    81,
    91,
    81,
    82,
    92,
    82,
    83,
    93,
    83,
    84,
    94,
    84,
    85,
    95,
    96,
    86,
    87,
    97,
    89,
    88,
    88,
    90,
    99,
    90,
    91,
    101,
    91,
    92,
    102,
    92,
    93,
    103,
    93,
    94,
    104,
    94,
    95,
    105,
    95,
    96,
    106,
    96,
    97,
    107,
    97,
    98,
    108,
    100,
    99,
    99,
    101,
    110,
    101,
    102,
    112,
    102,
    103,
    113,
    103,
    104,
    114,
    104,
    105,
    115,
    105,
    106,
    116,
    106,
    107,
    117,
    107,
    108,
    118,
    108,
    109,
    119;
   }
  }
 }
}

AnimationSet {
 
}