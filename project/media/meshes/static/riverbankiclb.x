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
   0.960294,-0.000000,-0.278991,0.000000,-0.260001,0.362628,-0.894930,0.000000,0.101170,0.931934,0.348229,0.000000,33.795502,261.149750,127.478745,1.000000;;
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
   331;
   -49.999996;-0.005000;50.000000;,
   -39.999996;-0.005000;50.000000;,
   -39.999996;-0.005000;40.000000;,
   -49.999996;-0.005000;40.000000;,
   -29.999998;-0.005000;50.000000;,
   -29.999998;-0.005000;40.000000;,
   -19.999996;-0.005000;50.000000;,
   -19.999996;-0.005000;40.000000;,
   -9.999998;-0.005000;50.000000;,
   -9.999998;-0.005000;40.000000;,
   0.000002;-0.005000;50.000000;,
   0.000002;-0.005000;40.000000;,
   10.000002;-0.005000;50.000000;,
   10.000002;-0.005000;40.000000;,
   20.000002;-0.005000;50.000000;,
   20.000002;-0.005000;40.000000;,
   30.000002;-0.005000;50.000000;,
   30.000002;-2.005000;40.000000;,
   40.000000;-0.005000;50.000000;,
   40.000000;-6.005000;40.000000;,
   50.000000;-2.005000;50.000000;,
   50.000000;-12.005000;40.000000;,
   -39.999996;-0.005000;30.000002;,
   -49.999996;-0.005000;30.000002;,
   -29.999998;-0.005000;30.000002;,
   -19.999996;-0.005000;30.000002;,
   -9.999998;-0.005000;30.000002;,
   0.000002;-0.005000;30.000002;,
   10.000002;-0.005000;30.000002;,
   20.000002;-2.005000;30.000002;,
   30.000002;-6.005000;30.000002;,
   40.000000;-15.005000;30.000002;,
   50.000000;-17.004999;30.000002;,
   -39.999996;-0.005000;20.000002;,
   -49.999996;-0.005000;20.000002;,
   -29.999998;-0.005000;20.000002;,
   -19.999996;-0.005000;20.000002;,
   -9.999998;-0.005000;20.000002;,
   0.000002;-0.005000;20.000002;,
   10.000002;-2.005000;20.000002;,
   20.000002;-6.005000;20.000002;,
   30.000002;-15.005000;20.000002;,
   40.000000;-17.004999;20.000002;,
   50.000000;-20.004999;20.000002;,
   -39.999996;-0.005000;10.000002;,
   -49.999996;-0.005000;10.000002;,
   -29.999998;-0.005000;10.000002;,
   -19.999996;-0.005000;10.000002;,
   -9.999998;-0.005000;10.000002;,
   0.000002;-0.005000;10.000002;,
   10.000002;-6.005000;10.000002;,
   20.000002;-15.005000;10.000002;,
   30.000002;-17.004999;10.000002;,
   40.000000;-20.004999;10.000002;,
   45.000004;-20.004999;15.000002;,
   -39.999996;-0.005000;0.000002;,
   -49.999996;-0.005000;0.000002;,
   -29.999998;-0.005000;0.000002;,
   -19.999996;-0.005000;0.000002;,
   -9.999998;-0.005000;0.000002;,
   0.000002;-2.005000;0.000002;,
   10.000002;-12.005000;0.000002;,
   20.000002;-15.005000;0.000002;,
   30.000002;-20.004999;0.000002;,
   35.000004;-20.004999;5.000002;,
   -39.999996;-0.005000;-9.999998;,
   -49.999996;-0.005000;-9.999998;,
   -29.999998;-0.005000;-9.999998;,
   -19.999996;-0.005000;-9.999998;,
   -9.999998;-0.005000;-9.999998;,
   0.000002;-6.005000;-9.999998;,
   10.000002;-15.005000;-9.999998;,
   20.000002;-17.004999;-9.999998;,
   30.000002;-20.004999;-9.999998;,
   -39.999996;-0.005000;-19.999996;,
   -49.999996;-0.005000;-19.999996;,
   -29.999998;-0.005000;-19.999996;,
   -19.999996;-0.005000;-19.999996;,
   -9.999998;-2.005000;-19.999996;,
   0.000002;-10.005000;-19.999996;,
   10.000002;-15.005000;-19.999996;,
   20.000002;-20.004999;-19.999996;,
   25.000004;-20.004999;-14.999998;,
   -39.999996;-0.005000;-29.999998;,
   -49.999996;-0.005000;-29.999998;,
   -29.999998;-0.005000;-29.999998;,
   -19.999996;-0.005000;-29.999998;,
   -9.999998;-6.005000;-29.999998;,
   0.000002;-15.005000;-29.999998;,
   10.000002;-17.004999;-29.999998;,
   15.000002;-20.004999;-24.999996;,
   -39.999996;-0.005000;-39.999996;,
   -49.999996;-0.005000;-39.999996;,
   -29.999998;-0.005000;-39.999996;,
   -19.999996;-2.005000;-39.999996;,
   -9.999998;-6.005000;-39.999996;,
   0.000002;-15.005000;-39.999996;,
   10.000002;-20.004999;-39.999996;,
   15.000002;-20.004999;-34.999996;,
   -39.999996;-0.005000;-49.999996;,
   -49.999996;-0.005000;-49.999996;,
   -29.999998;-0.005000;-49.999996;,
   -19.999996;-2.005000;-49.999996;,
   -9.999998;-15.005000;-49.999996;,
   0.000002;-17.004999;-49.999996;,
   10.000002;-20.004999;-49.999996;,
   -39.999996;-0.005000;50.000000;,
   -39.999996;-0.005000;40.000000;,
   -29.999998;-0.005000;50.000000;,
   -29.999998;-0.005000;40.000000;,
   -19.999996;-0.005000;50.000000;,
   -19.999996;-0.005000;40.000000;,
   -9.999998;-0.005000;50.000000;,
   -9.999998;-0.005000;40.000000;,
   0.000002;-0.005000;50.000000;,
   0.000002;-0.005000;40.000000;,
   10.000002;-0.005000;50.000000;,
   10.000002;-0.005000;40.000000;,
   20.000002;-0.005000;50.000000;,
   20.000002;-0.005000;40.000000;,
   30.000002;-0.005000;50.000000;,
   30.000002;-2.005000;40.000000;,
   40.000000;-0.005000;50.000000;,
   40.000000;-6.005000;40.000000;,
   -39.999996;-0.005000;40.000000;,
   -29.999998;-0.005000;40.000000;,
   -39.999996;-0.005000;30.000002;,
   -29.999998;-0.005000;40.000000;,
   -19.999996;-0.005000;40.000000;,
   -29.999998;-0.005000;30.000002;,
   -19.999996;-0.005000;40.000000;,
   -9.999998;-0.005000;40.000000;,
   -19.999996;-0.005000;30.000002;,
   -9.999998;-0.005000;40.000000;,
   0.000002;-0.005000;40.000000;,
   -9.999998;-0.005000;30.000002;,
   0.000002;-0.005000;40.000000;,
   10.000002;-0.005000;40.000000;,
   0.000002;-0.005000;30.000002;,
   10.000002;-0.005000;40.000000;,
   20.000002;-0.005000;40.000000;,
   10.000002;-0.005000;30.000002;,
   20.000002;-0.005000;40.000000;,
   30.000002;-2.005000;40.000000;,
   20.000002;-2.005000;30.000002;,
   30.000002;-2.005000;40.000000;,
   40.000000;-6.005000;40.000000;,
   30.000002;-6.005000;30.000002;,
   40.000000;-6.005000;40.000000;,
   50.000000;-12.005000;40.000000;,
   40.000000;-15.005000;30.000002;,
   -39.999996;-0.005000;30.000002;,
   -29.999998;-0.005000;30.000002;,
   -39.999996;-0.005000;20.000002;,
   -29.999998;-0.005000;30.000002;,
   -19.999996;-0.005000;30.000002;,
   -29.999998;-0.005000;20.000002;,
   -19.999996;-0.005000;30.000002;,
   -9.999998;-0.005000;30.000002;,
   -19.999996;-0.005000;20.000002;,
   -9.999998;-0.005000;30.000002;,
   0.000002;-0.005000;30.000002;,
   -9.999998;-0.005000;20.000002;,
   0.000002;-0.005000;30.000002;,
   10.000002;-0.005000;30.000002;,
   0.000002;-0.005000;20.000002;,
   10.000002;-0.005000;30.000002;,
   10.000002;-2.005000;20.000002;,
   20.000002;-2.005000;30.000002;,
   30.000002;-6.005000;30.000002;,
   20.000002;-6.005000;20.000002;,
   30.000002;-6.005000;30.000002;,
   40.000000;-15.005000;30.000002;,
   30.000002;-15.005000;20.000002;,
   40.000000;-15.005000;30.000002;,
   50.000000;-17.004999;30.000002;,
   40.000000;-17.004999;20.000002;,
   -39.999996;-0.005000;10.000002;,
   -29.999998;-0.005000;10.000002;,
   -19.999996;-0.005000;10.000002;,
   -9.999998;-0.005000;10.000002;,
   0.000002;-0.005000;20.000002;,
   10.000002;-2.005000;20.000002;,
   0.000002;-0.005000;10.000002;,
   10.000002;-2.005000;20.000002;,
   20.000002;-6.005000;20.000002;,
   10.000002;-6.005000;10.000002;,
   20.000002;-6.005000;20.000002;,
   30.000002;-15.005000;20.000002;,
   20.000002;-15.005000;10.000002;,
   30.000002;-15.005000;20.000002;,
   40.000000;-17.004999;20.000002;,
   30.000002;-17.004999;10.000002;,
   40.000000;-17.004999;20.000002;,
   50.000000;-20.004999;20.000002;,
   40.000000;-20.004999;10.000002;,
   -49.999996;-0.005000;10.000002;,
   -39.999996;-0.005000;10.000002;,
   -39.999996;-0.005000;0.000002;,
   -29.999998;-0.005000;10.000002;,
   -19.999996;-0.005000;10.000002;,
   -29.999998;-0.005000;0.000002;,
   -19.999996;-0.005000;10.000002;,
   -9.999998;-0.005000;10.000002;,
   -19.999996;-0.005000;0.000002;,
   -9.999998;-0.005000;10.000002;,
   0.000002;-0.005000;10.000002;,
   -9.999998;-0.005000;0.000002;,
   0.000002;-0.005000;10.000002;,
   10.000002;-6.005000;10.000002;,
   0.000002;-2.005000;0.000002;,
   10.000002;-6.005000;10.000002;,
   20.000002;-15.005000;10.000002;,
   10.000002;-12.005000;0.000002;,
   20.000002;-15.005000;10.000002;,
   30.000002;-17.004999;10.000002;,
   20.000002;-15.005000;0.000002;,
   30.000002;-17.004999;10.000002;,
   40.000000;-20.004999;10.000002;,
   30.000002;-20.004999;0.000002;,
   40.000000;-20.004999;10.000002;,
   45.000004;-20.004999;15.000002;,
   35.000004;-20.004999;5.000002;,
   -49.999996;-0.005000;0.000002;,
   -39.999996;-0.005000;0.000002;,
   -39.999996;-0.005000;-9.999998;,
   -29.999998;-0.005000;0.000002;,
   -19.999996;-0.005000;0.000002;,
   -29.999998;-0.005000;-9.999998;,
   -19.999996;-0.005000;0.000002;,
   -9.999998;-0.005000;0.000002;,
   -19.999996;-0.005000;-9.999998;,
   -9.999998;-0.005000;0.000002;,
   0.000002;-2.005000;0.000002;,
   -9.999998;-0.005000;-9.999998;,
   0.000002;-2.005000;0.000002;,
   10.000002;-12.005000;0.000002;,
   0.000002;-6.005000;-9.999998;,
   10.000002;-12.005000;0.000002;,
   20.000002;-15.005000;0.000002;,
   10.000002;-15.005000;-9.999998;,
   20.000002;-15.005000;0.000002;,
   30.000002;-20.004999;0.000002;,
   20.000002;-17.004999;-9.999998;,
   -49.999996;-0.005000;-9.999998;,
   -39.999996;-0.005000;-9.999998;,
   -39.999996;-0.005000;-9.999998;,
   -29.999998;-0.005000;-9.999998;,
   -39.999996;-0.005000;-19.999996;,
   -29.999998;-0.005000;-9.999998;,
   -19.999996;-0.005000;-9.999998;,
   -29.999998;-0.005000;-19.999996;,
   -19.999996;-0.005000;-9.999998;,
   -9.999998;-0.005000;-9.999998;,
   -19.999996;-0.005000;-19.999996;,
   -9.999998;-0.005000;-9.999998;,
   0.000002;-6.005000;-9.999998;,
   -9.999998;-2.005000;-19.999996;,
   0.000002;-6.005000;-9.999998;,
   10.000002;-15.005000;-9.999998;,
   0.000002;-10.005000;-19.999996;,
   10.000002;-15.005000;-9.999998;,
   20.000002;-17.004999;-9.999998;,
   10.000002;-15.005000;-19.999996;,
   20.000002;-17.004999;-9.999998;,
   30.000002;-20.004999;-9.999998;,
   20.000002;-20.004999;-19.999996;,
   -49.999996;-0.005000;-19.999996;,
   -39.999996;-0.005000;-19.999996;,
   -39.999996;-0.005000;-19.999996;,
   -29.999998;-0.005000;-19.999996;,
   -39.999996;-0.005000;-29.999998;,
   -29.999998;-0.005000;-19.999996;,
   -19.999996;-0.005000;-19.999996;,
   -29.999998;-0.005000;-29.999998;,
   -19.999996;-0.005000;-19.999996;,
   -9.999998;-2.005000;-19.999996;,
   -19.999996;-0.005000;-29.999998;,
   -9.999998;-2.005000;-19.999996;,
   0.000002;-10.005000;-19.999996;,
   -9.999998;-6.005000;-29.999998;,
   0.000002;-10.005000;-19.999996;,
   10.000002;-15.005000;-19.999996;,
   0.000002;-15.005000;-29.999998;,
   10.000002;-15.005000;-19.999996;,
   20.000002;-20.004999;-19.999996;,
   10.000002;-17.004999;-29.999998;,
   20.000002;-20.004999;-19.999996;,
   25.000004;-20.004999;-14.999998;,
   15.000002;-20.004999;-24.999996;,
   -49.999996;-0.005000;-29.999998;,
   -39.999996;-0.005000;-29.999998;,
   -39.999996;-0.005000;-29.999998;,
   -29.999998;-0.005000;-29.999998;,
   -39.999996;-0.005000;-39.999996;,
   -29.999998;-0.005000;-29.999998;,
   -19.999996;-0.005000;-29.999998;,
   -29.999998;-0.005000;-39.999996;,
   -19.999996;-0.005000;-29.999998;,
   -9.999998;-6.005000;-29.999998;,
   -19.999996;-2.005000;-39.999996;,
   -9.999998;-6.005000;-29.999998;,
   0.000002;-15.005000;-29.999998;,
   -9.999998;-6.005000;-39.999996;,
   0.000002;-15.005000;-29.999998;,
   10.000002;-17.004999;-29.999998;,
   0.000002;-15.005000;-39.999996;,
   10.000002;-17.004999;-29.999998;,
   15.000002;-20.004999;-24.999996;,
   10.000002;-20.004999;-39.999996;,
   25.000004;-20.004999;-14.999998;,
   30.000002;-20.004999;-9.999998;,
   15.000002;-20.004999;-24.999996;,
   30.000002;-20.004999;-9.999998;,
   30.000002;-20.004999;0.000002;,
   15.000002;-20.004999;-24.999996;,
   -39.999996;-0.005000;-39.999996;,
   -29.999998;-0.005000;-39.999996;,
   -39.999996;-0.005000;-49.999996;,
   -29.999998;-0.005000;-39.999996;,
   -19.999996;-2.005000;-39.999996;,
   -29.999998;-0.005000;-49.999996;,
   -19.999996;-2.005000;-39.999996;,
   -9.999998;-6.005000;-39.999996;,
   -19.999996;-2.005000;-49.999996;,
   -9.999998;-6.005000;-39.999996;,
   0.000002;-15.005000;-39.999996;,
   -9.999998;-15.005000;-49.999996;,
   0.000002;-15.005000;-39.999996;,
   10.000002;-20.004999;-39.999996;,
   0.000002;-17.004999;-49.999996;;
   89;
   4;3,2,1,0;,
   4;107,5,4,106;,
   4;109,7,6,108;,
   4;111,9,8,110;,
   4;113,11,10,112;,
   4;115,13,12,114;,
   4;117,15,14,116;,
   4;119,17,16,118;,
   4;121,19,18,120;,
   4;123,21,20,122;,
   4;23,22,2,3;,
   4;126,24,125,124;,
   4;129,25,128,127;,
   4;132,26,131,130;,
   4;135,27,134,133;,
   4;138,28,137,136;,
   4;141,29,140,139;,
   4;144,30,143,142;,
   4;147,31,146,145;,
   4;150,32,149,148;,
   4;34,33,22,23;,
   4;153,35,152,151;,
   4;156,36,155,154;,
   4;159,37,158,157;,
   4;162,38,161,160;,
   4;165,39,164,163;,
   4;167,40,144,166;,
   4;170,41,169,168;,
   4;173,42,172,171;,
   4;176,43,175,174;,
   4;45,44,33,34;,
   4;177,46,35,153;,
   4;178,47,36,156;,
   4;179,48,37,159;,
   4;180,49,38,162;,
   4;183,50,182,181;,
   4;186,51,185,184;,
   4;189,52,188,187;,
   4;192,53,191,190;,
   4;195,54,194,193;,
   4;56,55,197,196;,
   4;198,57,46,177;,
   4;201,58,200,199;,
   4;204,59,203,202;,
   4;207,60,206,205;,
   4;210,61,209,208;,
   4;213,62,212,211;,
   4;216,63,215,214;,
   4;219,64,218,217;,
   3;222,221,220;,
   4;66,65,224,223;,
   4;225,67,57,198;,
   4;228,68,227,226;,
   4;231,69,230,229;,
   4;234,70,233,232;,
   4;237,71,236,235;,
   4;240,72,239,238;,
   4;243,73,242,241;,
   4;75,74,245,244;,
   4;248,76,247,246;,
   4;251,77,250,249;,
   4;254,78,253,252;,
   4;257,79,256,255;,
   4;260,80,259,258;,
   4;263,81,262,261;,
   4;266,82,265,264;,
   4;84,83,268,267;,
   4;271,85,270,269;,
   4;274,86,273,272;,
   4;277,87,276,275;,
   4;280,88,279,278;,
   4;283,89,282,281;,
   4;286,90,285,284;,
   3;289,288,287;,
   4;92,91,291,290;,
   4;294,93,293,292;,
   4;297,94,296,295;,
   4;300,95,299,298;,
   4;303,96,302,301;,
   4;306,97,305,304;,
   4;309,98,308,307;,
   3;312,311,310;,
   3;315,314,313;,
   4;100,99,91,92;,
   4;318,101,317,316;,
   4;321,102,320,319;,
   4;324,103,323,322;,
   4;327,104,326,325;,
   4;330,105,329,328;;

   MeshNormals {
    64;
    0.000000;-1.000000;0.000000;,
    0.000000;-0.983949;-0.178453;,
    0.000000;0.919145;-0.393919;,
    0.000000;0.995974;0.089638;,
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
    0.000000;1.000000;0.000000;,
    0.099015;0.990148;-0.099015;,
    0.099015;0.990148;-0.099015;,
    0.099015;0.990148;-0.099015;,
    0.099015;0.990148;-0.099015;,
    0.099015;0.990148;-0.099015;,
    0.099015;0.990148;-0.099015;,
    0.182574;0.912871;-0.365148;,
    0.196116;0.980581;-0.000000;,
    0.235702;0.942809;-0.235702;,
    0.235702;0.942809;-0.235702;,
    0.235702;0.942809;-0.235702;,
    0.276172;0.920575;-0.276172;,
    0.276172;0.920575;-0.276172;,
    0.276172;0.920575;-0.276172;,
    0.276172;0.920575;-0.276172;,
    0.298142;0.745356;-0.596285;,
    0.311400;0.778499;-0.544949;,
    0.313677;0.896221;-0.313677;,
    0.327088;0.934539;-0.140181;,
    0.327088;0.934539;-0.140181;,
    0.327088;0.934539;-0.140181;,
    0.365148;0.912871;-0.182574;,
    0.365148;0.912871;-0.182574;,
    0.365148;0.912871;-0.182574;,
    0.369800;0.924500;-0.092450;,
    0.369800;0.924500;-0.092450;,
    0.406579;0.903508;-0.135526;,
    0.434135;0.789337;-0.434135;,
    0.434135;0.789337;-0.434135;,
    0.434136;0.789337;-0.434135;,
    0.445436;0.890871;-0.089087;,
    0.478537;0.736210;-0.478537;,
    0.478537;0.736210;-0.478537;,
    0.478537;0.736210;-0.478537;,
    0.498273;0.830455;-0.249136;,
    0.522937;0.804518;-0.281581;,
    0.556890;0.795557;-0.238667;,
    0.565916;0.808452;-0.161690;,
    0.596285;0.745356;-0.298142;,
    0.612637;0.720750;-0.324337;,
    0.612638;0.720750;-0.324337;,
    0.667592;0.702728;-0.245955;,
    0.668965;0.743294;0.000000;;
    89;
    4;5,5,5,5;,
    4;15,15,15,15;,
    4;11,11,11,11;,
    4;16,16,16,16;,
    4;19,19,19,19;,
    4;9,9,9,9;,
    4;6,6,6,6;,
    4;24,24,24,24;,
    4;27,27,27,27;,
    4;36,36,36,36;,
    4;5,5,5,5;,
    4;18,18,18,18;,
    4;10,10,10,10;,
    4;17,17,17,17;,
    4;20,20,20,20;,
    4;8,8,8,8;,
    4;22,22,22,22;,
    4;35,35,35,35;,
    4;52,52,52,52;,
    4;37,37,37,37;,
    4;5,5,5,5;,
    4;15,15,15,15;,
    4;11,11,11,11;,
    4;16,16,16,16;,
    4;19,19,19,19;,
    4;26,26,26,26;,
    4;35,35,35,35;,
    4;53,53,53,53;,
    4;50,50,50,50;,
    4;30,30,30,30;,
    4;5,5,5,5;,
    4;15,15,15,15;,
    4;11,11,11,11;,
    4;16,16,16,16;,
    4;19,19,19,19;,
    4;43,43,43,43;,
    4;54,54,54,54;,
    4;48,48,48,48;,
    4;31,31,31,31;,
    4;32,32,32,32;,
    4;4,4,4,4;,
    4;15,15,15,15;,
    4;12,12,12,12;,
    4;15,15,15,15;,
    4;23,23,23,23;,
    4;59,59,59,59;,
    4;55,55,55,55;,
    4;39,39,39,39;,
    4;34,34,34,34;,
    3;3,3,3;,
    4;6,6,6,6;,
    4;15,15,15,15;,
    4;11,11,11,11;,
    4;16,16,16,16;,
    4;42,42,42,42;,
    4;62,62,62,62;,
    4;29,29,29,29;,
    4;45,45,45,45;,
    4;5,5,5,5;,
    4;18,18,18,18;,
    4;10,10,10,10;,
    4;25,25,25,25;,
    4;57,57,57,57;,
    4;58,58,58,58;,
    4;40,40,40,40;,
    4;33,33,33,33;,
    4;7,7,7,7;,
    4;14,14,14,14;,
    4;13,13,13,13;,
    4;44,44,44,44;,
    4;60,60,60,60;,
    4;38,38,38,38;,
    4;56,56,56,56;,
    3;2,2,2;,
    4;5,5,5,5;,
    4;18,18,18,18;,
    4;21,21,21,21;,
    4;51,51,51,51;,
    4;63,63,63,63;,
    4;41,41,41,41;,
    4;47,47,47,47;,
    3;1,1,1;,
    3;0,0,0;,
    4;5,5,5,5;,
    4;15,15,15,15;,
    4;28,28,28,28;,
    4;61,61,61,61;,
    4;49,49,49,49;,
    4;46,46,46,46;;
   }

   MeshTextureCoords {
    331;
    0.003371;0.999826;,
    0.062344;0.999826;,
    0.062344;0.940852;,
    0.003371;0.940852;,
    0.121317;0.999826;,
    0.121317;0.940852;,
    0.180290;0.999826;,
    0.180290;0.940852;,
    0.239263;0.999826;,
    0.239263;0.940852;,
    0.298236;0.999826;,
    0.298236;0.940852;,
    0.357210;0.999826;,
    0.357210;0.940852;,
    0.416183;0.999826;,
    0.416183;0.940852;,
    0.475156;0.999826;,
    0.475156;0.940852;,
    0.534129;0.999826;,
    0.642449;0.928932;,
    0.634096;1.000000;,
    0.838322;0.928932;,
    0.062344;0.881879;,
    0.003371;0.881879;,
    0.121317;0.881879;,
    0.180290;0.881879;,
    0.239263;0.881879;,
    0.298236;0.881879;,
    0.357210;0.881879;,
    0.416183;0.881879;,
    0.579890;0.835172;,
    0.750235;0.809644;,
    0.931925;0.860700;,
    0.062344;0.822906;,
    0.003371;0.822906;,
    0.121317;0.822906;,
    0.180290;0.822906;,
    0.239263;0.822906;,
    0.298236;0.822906;,
    0.357210;0.822906;,
    0.500313;0.786796;,
    0.642293;0.755595;,
    0.795618;0.721557;,
    1.000000;0.800000;,
    0.062344;0.763933;,
    0.003371;0.763933;,
    0.121317;0.763933;,
    0.180290;0.763933;,
    0.239263;0.763933;,
    0.298236;0.763933;,
    0.357210;0.763933;,
    0.500313;0.715728;,
    0.639456;0.639143;,
    0.850000;0.650000;,
    0.950000;0.750000;,
    0.062344;0.704960;,
    0.003371;0.704960;,
    0.121317;0.704960;,
    0.180290;0.704960;,
    0.239263;0.704960;,
    0.298236;0.704960;,
    0.429245;0.644660;,
    0.505986;0.638987;,
    0.700000;0.500000;,
    0.800000;0.600000;,
    0.062344;0.645987;,
    0.003371;0.645987;,
    0.121317;0.645987;,
    0.180290;0.645987;,
    0.239263;0.645987;,
    0.298236;0.645987;,
    0.429245;0.573592;,
    0.562715;0.545227;,
    0.650000;0.450000;,
    0.062344;0.587014;,
    0.003371;0.587014;,
    0.121317;0.587014;,
    0.180290;0.587014;,
    0.239263;0.587014;,
    0.358177;0.502524;,
    0.429245;0.502524;,
    0.545696;0.414593;,
    0.600000;0.400000;,
    0.062344;0.624480;,
    0.003371;0.624480;,
    0.121317;0.624480;,
    0.180290;0.528041;,
    0.239263;0.528041;,
    0.358177;0.431456;,
    0.440591;0.349198;,
    0.500000;0.300000;,
    0.062344;0.565507;,
    0.003371;0.565507;,
    0.121317;0.565507;,
    0.106542;0.531470;,
    0.156631;0.374570;,
    0.222026;0.204382;,
    0.350000;0.150000;,
    0.400000;0.200000;,
    0.003182;0.609563;,
    0.001366;0.572068;,
    0.004998;0.550618;,
    0.006814;0.517201;,
    0.073591;0.166932;,
    0.141301;0.089121;,
    0.200000;0.000000;,
    0.062344;0.999826;,
    0.062344;0.940852;,
    0.121317;0.999826;,
    0.121317;0.940852;,
    0.180290;0.999826;,
    0.180290;0.940852;,
    0.239263;0.999826;,
    0.239263;0.940852;,
    0.298236;0.999826;,
    0.298236;0.940852;,
    0.357210;0.999826;,
    0.357210;0.940852;,
    0.416183;0.999826;,
    0.416183;0.940852;,
    0.475156;0.999826;,
    0.475156;0.940852;,
    0.534129;0.999826;,
    0.642449;0.928932;,
    0.062344;0.940852;,
    0.121317;0.940852;,
    0.062344;0.881879;,
    0.121317;0.940852;,
    0.180290;0.940852;,
    0.121317;0.881879;,
    0.180290;0.940852;,
    0.239263;0.940852;,
    0.180290;0.881879;,
    0.239263;0.940852;,
    0.298236;0.940852;,
    0.239263;0.881879;,
    0.298236;0.940852;,
    0.357210;0.940852;,
    0.298236;0.881879;,
    0.357210;0.940852;,
    0.416183;0.940852;,
    0.357210;0.881879;,
    0.416183;0.940852;,
    0.475156;0.940852;,
    0.416183;0.881879;,
    0.475156;0.940852;,
    0.642449;0.928932;,
    0.579890;0.835172;,
    0.642449;0.928932;,
    0.838322;0.928932;,
    0.750235;0.809644;,
    0.062344;0.881879;,
    0.121317;0.881879;,
    0.062344;0.822906;,
    0.121317;0.881879;,
    0.180290;0.881879;,
    0.121317;0.822906;,
    0.180290;0.881879;,
    0.239263;0.881879;,
    0.180290;0.822906;,
    0.239263;0.881879;,
    0.298236;0.881879;,
    0.239263;0.822906;,
    0.298236;0.881879;,
    0.357210;0.881879;,
    0.298236;0.822906;,
    0.357210;0.881879;,
    0.357210;0.822906;,
    0.416183;0.881879;,
    0.579890;0.835172;,
    0.500313;0.786796;,
    0.579890;0.835172;,
    0.750235;0.809644;,
    0.642293;0.755595;,
    0.750235;0.809644;,
    0.931925;0.860700;,
    0.795618;0.721557;,
    0.062344;0.763933;,
    0.121317;0.763933;,
    0.180290;0.763933;,
    0.239263;0.763933;,
    0.298236;0.822906;,
    0.357210;0.822906;,
    0.298236;0.763933;,
    0.357210;0.822906;,
    0.500313;0.786796;,
    0.357210;0.763933;,
    0.500313;0.786796;,
    0.642293;0.755595;,
    0.500313;0.715728;,
    0.642293;0.755595;,
    0.795618;0.721557;,
    0.639456;0.639143;,
    0.795618;0.721557;,
    1.000000;0.800000;,
    0.850000;0.650000;,
    0.003371;0.763933;,
    0.062344;0.763933;,
    0.062344;0.704960;,
    0.121317;0.763933;,
    0.180290;0.763933;,
    0.121317;0.704960;,
    0.180290;0.763933;,
    0.239263;0.763933;,
    0.180290;0.704960;,
    0.239263;0.763933;,
    0.298236;0.763933;,
    0.239263;0.704960;,
    0.298236;0.763933;,
    0.357210;0.763933;,
    0.298236;0.704960;,
    0.357210;0.763933;,
    0.500313;0.715728;,
    0.429245;0.644660;,
    0.500313;0.715728;,
    0.639456;0.639143;,
    0.505986;0.638987;,
    0.639456;0.639143;,
    0.850000;0.650000;,
    0.700000;0.500000;,
    0.850000;0.650000;,
    0.950000;0.750000;,
    0.800000;0.600000;,
    0.003371;0.704960;,
    0.062344;0.704960;,
    0.062344;0.645987;,
    0.121317;0.704960;,
    0.180290;0.704960;,
    0.121317;0.645987;,
    0.180290;0.704960;,
    0.239263;0.704960;,
    0.180290;0.645987;,
    0.239263;0.704960;,
    0.298236;0.704960;,
    0.239263;0.645987;,
    0.298236;0.704960;,
    0.429245;0.644660;,
    0.298236;0.645987;,
    0.429245;0.644660;,
    0.505986;0.638987;,
    0.429245;0.573592;,
    0.505986;0.638987;,
    0.700000;0.500000;,
    0.562715;0.545227;,
    0.003371;0.645987;,
    0.062344;0.645987;,
    0.062344;0.645987;,
    0.121317;0.645987;,
    0.062344;0.587014;,
    0.121317;0.645987;,
    0.180290;0.645987;,
    0.121317;0.587014;,
    0.180290;0.645987;,
    0.239263;0.645987;,
    0.180290;0.587014;,
    0.239263;0.645987;,
    0.298236;0.645987;,
    0.239263;0.587014;,
    0.298236;0.645987;,
    0.429245;0.573592;,
    0.358177;0.502524;,
    0.429245;0.573592;,
    0.562715;0.545227;,
    0.429245;0.502524;,
    0.562715;0.545227;,
    0.650000;0.450000;,
    0.545696;0.414593;,
    0.003371;0.587014;,
    0.062344;0.587014;,
    0.062344;0.587014;,
    0.121317;0.587014;,
    0.062344;0.624480;,
    0.121317;0.587014;,
    0.180290;0.587014;,
    0.121317;0.624480;,
    0.180290;0.587014;,
    0.239263;0.587014;,
    0.180290;0.528041;,
    0.239263;0.587014;,
    0.358177;0.502524;,
    0.239263;0.528041;,
    0.358177;0.502524;,
    0.429245;0.502524;,
    0.358177;0.431456;,
    0.429245;0.502524;,
    0.545696;0.414593;,
    0.440591;0.349198;,
    0.545696;0.414593;,
    0.600000;0.400000;,
    0.500000;0.300000;,
    0.003371;0.624480;,
    0.062344;0.624480;,
    0.062344;0.624480;,
    0.121317;0.624480;,
    0.062344;0.565507;,
    0.121317;0.624480;,
    0.180290;0.528041;,
    0.121317;0.565507;,
    0.180290;0.528041;,
    0.239263;0.528041;,
    0.106542;0.531470;,
    0.239263;0.528041;,
    0.358177;0.431456;,
    0.156631;0.374570;,
    0.358177;0.431456;,
    0.440591;0.349198;,
    0.222026;0.204382;,
    0.440591;0.349198;,
    0.500000;0.300000;,
    0.350000;0.150000;,
    0.600000;0.400000;,
    0.650000;0.450000;,
    0.500000;0.300000;,
    0.650000;0.450000;,
    0.700000;0.500000;,
    0.500000;0.300000;,
    0.062344;0.565507;,
    0.121317;0.565507;,
    0.003182;0.609563;,
    0.121317;0.565507;,
    0.106542;0.531470;,
    0.004998;0.550618;,
    0.106542;0.531470;,
    0.156631;0.374570;,
    0.006814;0.517201;,
    0.156631;0.374570;,
    0.222026;0.204382;,
    0.073591;0.166932;,
    0.222026;0.204382;,
    0.350000;0.150000;,
    0.141301;0.089121;;
   }

   MeshMaterialList {
    1;
    89;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
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

    Material lambert3SG {
     0.800000;0.800000;0.800000;1.000000;;
     0.000000;
     0.000000;0.000000;0.000000;;
     0.000000;0.000000;0.000000;;

     TextureFilename {
      "riverbankbend.bmp";
     }
    }
   }

   VertexDuplicationIndices {
    331;
    106;
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
    44,
    46,
    47,
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
    52,
    53,
    63,
    53,
    54,
    64,
    56,
    55,
    65,
    57,
    58,
    67,
    58,
    59,
    68,
    59,
    60,
    69,
    60,
    61,
    70,
    61,
    62,
    71,
    62,
    63,
    72,
    66,
    65,
    65,
    67,
    74,
    67,
    68,
    76,
    68,
    69,
    77,
    69,
    70,
    78,
    70,
    71,
    79,
    71,
    72,
    80,
    72,
    73,
    81,
    75,
    74,
    74,
    76,
    83,
    76,
    77,
    85,
    77,
    78,
    86,
    78,
    79,
    87,
    79,
    80,
    88,
    80,
    81,
    89,
    81,
    82,
    90,
    84,
    83,
    83,
    85,
    91,
    85,
    86,
    93,
    86,
    87,
    94,
    87,
    88,
    95,
    88,
    89,
    96,
    89,
    90,
    97,
    82,
    73,
    90,
    73,
    63,
    90,
    91,
    93,
    99,
    93,
    94,
    101,
    94,
    95,
    102,
    95,
    96,
    103,
    96,
    97,
    104;
   }
  }
 }
}

AnimationSet {
 
}