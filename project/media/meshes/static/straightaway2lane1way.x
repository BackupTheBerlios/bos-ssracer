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
   1.000000,0.000000,0.000000,0.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,0.161987,100.000000,0.032397,1.000000;;
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
   143;
   -6.000000;0.250000;15.000000;,
   -4.000000;0.250000;15.000000;,
   -4.000000;0.250000;12.000000;,
   -6.000000;0.250000;12.000000;,
   -4.000000;0.000000;15.000000;,
   -4.000000;0.000000;12.000000;,
   -2.513163;0.000000;15.000000;,
   -2.513538;0.000000;12.000000;,
   0.000000;0.000000;15.000000;,
   0.000000;0.000000;12.000000;,
   2.498222;0.000000;15.000000;,
   2.497847;0.000000;12.000000;,
   4.000000;0.000000;15.000000;,
   4.000000;0.000000;12.000000;,
   4.000000;0.250000;15.000000;,
   4.000000;0.250000;12.000000;,
   6.000000;0.250000;15.000000;,
   6.000000;0.250000;12.000000;,
   -4.000000;0.250000;8.999999;,
   -6.000000;0.250000;8.999999;,
   -4.000000;0.000000;8.999999;,
   -2.513538;0.000000;8.999999;,
   0.000000;0.000000;8.999999;,
   2.497847;0.000000;8.999999;,
   4.000000;0.000000;8.999999;,
   4.000000;0.250000;8.999999;,
   6.000000;0.250000;8.999999;,
   -4.000000;0.250000;6.000000;,
   -6.000000;0.250000;6.000000;,
   -4.000000;0.000000;6.000000;,
   -2.513538;0.000000;6.000000;,
   0.000000;0.000000;6.000000;,
   2.497847;0.000000;6.000000;,
   4.000000;0.000000;6.000000;,
   4.000000;0.250000;6.000000;,
   6.000000;0.250000;6.000000;,
   -4.000000;0.250000;3.000000;,
   -6.000000;0.250000;3.000000;,
   -4.000000;0.000000;3.000000;,
   -2.513538;0.000000;3.000000;,
   0.000000;0.000000;3.000000;,
   2.497847;0.000000;3.000000;,
   4.000000;0.000000;3.000000;,
   4.000000;0.250000;3.000000;,
   6.000000;0.250000;3.000000;,
   -4.000000;0.250000;0.000000;,
   -6.000000;0.250000;0.000000;,
   -4.000000;0.000000;0.000000;,
   -2.513538;0.000000;0.000000;,
   0.000000;0.000000;0.000000;,
   2.497847;0.000000;0.000000;,
   4.000000;0.000000;0.000000;,
   4.000000;0.250000;0.000000;,
   6.000000;0.250000;0.000000;,
   -4.000000;0.250000;-3.000000;,
   -6.000000;0.250000;-3.000000;,
   -4.000000;0.000000;-3.000000;,
   -2.513538;0.000000;-3.000000;,
   0.000000;0.000000;-3.000000;,
   2.497847;0.000000;-3.000000;,
   4.000000;0.000000;-3.000000;,
   4.000000;0.250000;-3.000000;,
   6.000000;0.250000;-3.000000;,
   -4.000000;0.250000;-6.000000;,
   -6.000000;0.250000;-6.000000;,
   -4.000000;0.000000;-6.000000;,
   -2.513538;0.000000;-6.000000;,
   0.000000;0.000000;-6.000000;,
   2.497847;0.000000;-6.000000;,
   4.000000;0.000000;-6.000000;,
   4.000000;0.250000;-6.000000;,
   6.000000;0.250000;-6.000000;,
   -4.000000;0.250000;-9.000000;,
   -6.000000;0.250000;-9.000000;,
   -4.000000;0.000000;-9.000000;,
   -2.513538;0.000000;-9.000000;,
   0.000000;0.000000;-9.000000;,
   2.497847;0.000000;-9.000000;,
   4.000000;0.000000;-9.000000;,
   4.000000;0.250000;-9.000000;,
   6.000000;0.250000;-9.000000;,
   -4.000000;0.250000;-11.999999;,
   -6.000000;0.250000;-11.999999;,
   -4.000000;0.000000;-11.999999;,
   -2.513538;0.000000;-11.999999;,
   0.000000;0.000000;-11.999999;,
   2.497847;0.000000;-11.999999;,
   4.000000;0.000000;-12.000000;,
   4.000000;0.250000;-12.000000;,
   6.000000;0.250000;-12.000000;,
   -4.000000;0.250000;-14.999996;,
   -6.000000;0.250000;-14.999996;,
   -4.000000;0.000000;-14.999996;,
   -2.513538;0.000000;-14.999996;,
   0.000000;0.000000;-14.999996;,
   2.497847;0.000000;-14.999996;,
   4.000000;0.000000;-14.999996;,
   4.000000;0.250000;-14.999996;,
   6.000000;0.250000;-14.999996;,
   -4.000000;0.250000;15.000000;,
   -4.000000;0.250000;12.000000;,
   -4.000000;0.000000;15.000000;,
   -4.000000;0.000000;12.000000;,
   4.000000;0.000000;15.000000;,
   4.000000;0.000000;12.000000;,
   4.000000;0.250000;15.000000;,
   4.000000;0.250000;12.000000;,
   -4.000000;0.250000;8.999999;,
   -4.000000;0.000000;8.999999;,
   4.000000;0.000000;8.999999;,
   4.000000;0.250000;8.999999;,
   -4.000000;0.250000;6.000000;,
   -4.000000;0.000000;6.000000;,
   4.000000;0.000000;6.000000;,
   4.000000;0.250000;6.000000;,
   -4.000000;0.250000;3.000000;,
   -4.000000;0.000000;3.000000;,
   4.000000;0.000000;3.000000;,
   4.000000;0.250000;3.000000;,
   -4.000000;0.250000;0.000000;,
   -4.000000;0.000000;0.000000;,
   4.000000;0.000000;0.000000;,
   4.000000;0.250000;0.000000;,
   -4.000000;0.250000;-3.000000;,
   -4.000000;0.000000;-3.000000;,
   4.000000;0.000000;-3.000000;,
   4.000000;0.250000;-3.000000;,
   -4.000000;0.250000;-6.000000;,
   -4.000000;0.000000;-6.000000;,
   4.000000;0.000000;-6.000000;,
   4.000000;0.250000;-6.000000;,
   -4.000000;0.250000;-9.000000;,
   -4.000000;0.000000;-9.000000;,
   4.000000;0.000000;-9.000000;,
   4.000000;0.250000;-9.000000;,
   -4.000000;0.250000;-11.999999;,
   -4.000000;0.000000;-11.999999;,
   4.000000;0.000000;-12.000000;,
   4.000000;0.250000;-12.000000;,
   -4.000000;0.250000;-14.999996;,
   -4.000000;0.000000;-14.999996;,
   4.000000;0.000000;-14.999996;,
   4.000000;0.250000;-14.999996;;
   80;
   4;3,2,1,0;,
   4;100,5,4,99;,
   4;102,7,6,101;,
   4;7,9,8,6;,
   4;9,11,10,8;,
   4;11,13,12,10;,
   4;104,15,14,103;,
   4;106,17,16,105;,
   4;19,18,2,3;,
   4;107,20,5,100;,
   4;108,21,7,102;,
   4;21,22,9,7;,
   4;22,23,11,9;,
   4;23,24,13,11;,
   4;109,25,15,104;,
   4;110,26,17,106;,
   4;28,27,18,19;,
   4;111,29,20,107;,
   4;112,30,21,108;,
   4;30,31,22,21;,
   4;31,32,23,22;,
   4;32,33,24,23;,
   4;113,34,25,109;,
   4;114,35,26,110;,
   4;37,36,27,28;,
   4;115,38,29,111;,
   4;116,39,30,112;,
   4;39,40,31,30;,
   4;40,41,32,31;,
   4;41,42,33,32;,
   4;117,43,34,113;,
   4;118,44,35,114;,
   4;46,45,36,37;,
   4;119,47,38,115;,
   4;120,48,39,116;,
   4;48,49,40,39;,
   4;49,50,41,40;,
   4;50,51,42,41;,
   4;121,52,43,117;,
   4;122,53,44,118;,
   4;55,54,45,46;,
   4;123,56,47,119;,
   4;124,57,48,120;,
   4;57,58,49,48;,
   4;58,59,50,49;,
   4;59,60,51,50;,
   4;125,61,52,121;,
   4;126,62,53,122;,
   4;64,63,54,55;,
   4;127,65,56,123;,
   4;128,66,57,124;,
   4;66,67,58,57;,
   4;67,68,59,58;,
   4;68,69,60,59;,
   4;129,70,61,125;,
   4;130,71,62,126;,
   4;73,72,63,64;,
   4;131,74,65,127;,
   4;132,75,66,128;,
   4;75,76,67,66;,
   4;76,77,68,67;,
   4;77,78,69,68;,
   4;133,79,70,129;,
   4;134,80,71,130;,
   4;82,81,72,73;,
   4;135,83,74,131;,
   4;136,84,75,132;,
   4;84,85,76,75;,
   4;85,86,77,76;,
   4;86,87,78,77;,
   4;137,88,79,133;,
   4;138,89,80,134;,
   4;91,90,81,82;,
   4;139,92,83,135;,
   4;140,93,84,136;,
   4;93,94,85,84;,
   4;94,95,86,85;,
   4;95,96,87,86;,
   4;141,97,88,137;,
   4;142,98,89,138;;

   MeshNormals {
    3;
    -1.000000;0.000000;0.000000;,
    0.000000;1.000000;0.000000;,
    1.000000;0.000000;0.000000;;
    80;
    4;1,1,1,1;,
    4;2,2,2,2;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;0,0,0,0;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;2,2,2,2;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;0,0,0,0;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;2,2,2,2;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;0,0,0,0;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;2,2,2,2;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;0,0,0,0;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;2,2,2,2;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;0,0,0,0;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;2,2,2,2;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;0,0,0,0;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;2,2,2,2;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;0,0,0,0;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;2,2,2,2;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;0,0,0,0;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;2,2,2,2;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;0,0,0,0;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;2,2,2,2;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;1,1,1,1;,
    4;0,0,0,0;,
    4;1,1,1,1;;
   }

   MeshTextureCoords {
    143;
    0.002093;0.997820;,
    0.200570;0.997820;,
    0.200570;0.846154;,
    0.001090;0.847789;,
    0.277211;0.997820;,
    0.277211;0.846154;,
    0.332415;0.997820;,
    0.332415;0.846154;,
    0.501507;0.997820;,
    0.501507;0.846154;,
    0.664304;0.997820;,
    0.664304;0.846154;,
    0.727376;0.997820;,
    0.727376;0.846154;,
    0.799615;0.997820;,
    0.799615;0.846154;,
    0.998081;0.997820;,
    0.998452;0.847789;,
    0.200570;0.730769;,
    0.002180;0.730769;,
    0.277211;0.730769;,
    0.332415;0.730769;,
    0.501507;0.730769;,
    0.664304;0.730769;,
    0.727376;0.730769;,
    0.799615;0.730769;,
    0.999084;0.730769;,
    0.200570;0.615385;,
    0.002180;0.615385;,
    0.277211;0.615385;,
    0.332415;0.615385;,
    0.501507;0.615385;,
    0.664304;0.615385;,
    0.727376;0.615385;,
    0.799615;0.615385;,
    0.999084;0.615385;,
    0.200570;0.538462;,
    0.002180;0.538462;,
    0.277211;0.538462;,
    0.332415;0.538462;,
    0.501507;0.538462;,
    0.664304;0.538462;,
    0.727376;0.538462;,
    0.799615;0.538462;,
    0.999084;0.538462;,
    0.200570;0.461538;,
    0.002180;0.461538;,
    0.277211;0.461538;,
    0.332415;0.461538;,
    0.501507;0.461538;,
    0.664304;0.461538;,
    0.727376;0.461538;,
    0.799615;0.461538;,
    0.999084;0.461538;,
    0.200570;0.384615;,
    0.002180;0.384615;,
    0.277211;0.384615;,
    0.332415;0.384615;,
    0.501507;0.384615;,
    0.664304;0.384615;,
    0.727376;0.384615;,
    0.799615;0.384615;,
    0.999084;0.384615;,
    0.200570;0.307692;,
    0.002180;0.307692;,
    0.277211;0.307692;,
    0.332415;0.307692;,
    0.501507;0.307692;,
    0.664304;0.307692;,
    0.727376;0.307692;,
    0.799615;0.307692;,
    0.999084;0.307692;,
    0.200570;0.192308;,
    0.002180;0.192308;,
    0.277211;0.192308;,
    0.332415;0.192308;,
    0.501507;0.192308;,
    0.664304;0.192308;,
    0.727376;0.192308;,
    0.799615;0.192308;,
    0.999084;0.192308;,
    0.200570;0.076923;,
    0.001090;0.075833;,
    0.277211;0.076923;,
    0.332415;0.076923;,
    0.501507;0.076923;,
    0.664304;0.076923;,
    0.727376;0.076923;,
    0.799615;0.076923;,
    0.998452;0.075833;,
    0.200570;-0.003440;,
    0.002093;-0.003440;,
    0.277211;-0.003440;,
    0.332415;-0.003440;,
    0.501507;-0.003440;,
    0.664304;-0.003440;,
    0.727376;-0.003440;,
    0.799615;-0.003440;,
    0.998081;-0.003440;,
    0.200570;0.997820;,
    0.200570;0.846154;,
    0.277211;0.997820;,
    0.277211;0.846154;,
    0.727376;0.997820;,
    0.727376;0.846154;,
    0.799615;0.997820;,
    0.799615;0.846154;,
    0.200570;0.730769;,
    0.277211;0.730769;,
    0.727376;0.730769;,
    0.799615;0.730769;,
    0.200570;0.615385;,
    0.277211;0.615385;,
    0.727376;0.615385;,
    0.799615;0.615385;,
    0.200570;0.538462;,
    0.277211;0.538462;,
    0.727376;0.538462;,
    0.799615;0.538462;,
    0.200570;0.461538;,
    0.277211;0.461538;,
    0.727376;0.461538;,
    0.799615;0.461538;,
    0.200570;0.384615;,
    0.277211;0.384615;,
    0.727376;0.384615;,
    0.799615;0.384615;,
    0.200570;0.307692;,
    0.277211;0.307692;,
    0.727376;0.307692;,
    0.799615;0.307692;,
    0.200570;0.192308;,
    0.277211;0.192308;,
    0.727376;0.192308;,
    0.799615;0.192308;,
    0.200570;0.076923;,
    0.277211;0.076923;,
    0.727376;0.076923;,
    0.799615;0.076923;,
    0.200570;-0.003440;,
    0.277211;-0.003440;,
    0.727376;-0.003440;,
    0.799615;-0.003440;;
   }

   MeshMaterialList {
    1;
    80;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
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
      "straightaway2lane1way.bmp";
     }
    }
   }

   VertexDuplicationIndices {
    143;
    99;
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
    1,
    2,
    4,
    5,
    12,
    13,
    14,
    15,
    18,
    20,
    24,
    25,
    27,
    29,
    33,
    34,
    36,
    38,
    42,
    43,
    45,
    47,
    51,
    52,
    54,
    56,
    60,
    61,
    63,
    65,
    69,
    70,
    72,
    74,
    78,
    79,
    81,
    83,
    87,
    88,
    90,
    92,
    96,
    97;
   }
  }
 }
}

AnimationSet {
 
}