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
   273;
   -8.000000;0.250000;15.000000;,
   -6.000000;0.250000;15.000000;,
   -6.000000;0.250000;8.000000;,
   -8.000000;0.250000;8.000000;,
   -6.000000;0.000000;15.000000;,
   -6.000000;0.000000;8.000000;,
   -5.000000;0.000000;15.000000;,
   -5.000000;0.000000;8.000000;,
   -2.512788;0.000000;15.000000;,
   -2.513538;0.000000;8.000000;,
   0.000000;0.000000;15.000000;,
   0.000000;0.000000;8.000000;,
   2.498597;0.000000;15.000000;,
   2.497847;0.000000;8.000000;,
   5.000000;0.000000;15.000000;,
   5.000000;0.000000;8.000000;,
   6.000000;0.000000;15.000000;,
   6.000000;0.000000;8.000000;,
   6.000000;0.250000;15.000000;,
   6.000000;0.250000;8.000000;,
   8.000000;0.250000;15.000000;,
   8.000000;0.250000;8.000000;,
   -6.000000;0.250000;6.000000;,
   -8.000000;0.250000;6.000000;,
   -6.000000;0.000000;6.000000;,
   -5.000000;0.000000;6.000000;,
   -2.513538;0.000000;6.000000;,
   0.000000;0.000000;6.000000;,
   2.497847;0.000000;6.000000;,
   5.000000;0.000000;6.000000;,
   6.000000;0.000000;5.999999;,
   6.000000;0.250000;5.999999;,
   8.000000;0.250000;4.000000;,
   8.000000;0.000000;4.000000;,
   -6.000000;0.250000;4.000000;,
   -8.000000;0.250000;4.000000;,
   -6.000000;0.000000;4.000000;,
   -5.000000;0.000000;4.000000;,
   -2.513538;0.000000;4.000000;,
   0.000000;0.000000;4.000000;,
   2.497847;0.000000;4.000000;,
   5.000000;0.000000;4.000000;,
   6.000000;0.000000;4.000000;,
   -6.000000;0.250000;2.000000;,
   -8.000000;0.250000;2.000000;,
   -6.000000;0.000000;2.000000;,
   -5.000000;0.000000;2.000000;,
   -2.513538;0.000000;2.000000;,
   0.000000;0.000000;2.000000;,
   2.497847;0.000000;2.000000;,
   5.000000;0.000000;2.000000;,
   6.000000;0.000000;2.000000;,
   8.000000;0.000000;2.000000;,
   -6.000000;0.250000;0.000000;,
   -8.000000;0.250000;0.000000;,
   -6.000000;0.000000;0.000000;,
   -5.000000;0.000000;0.000000;,
   -2.513538;0.000000;0.000000;,
   0.000000;0.000000;0.000000;,
   2.497847;0.000000;0.000000;,
   5.000000;0.000000;0.000000;,
   6.000000;0.000000;0.000000;,
   8.000000;0.000000;0.000000;,
   -6.000000;0.250000;-4.000000;,
   -8.000000;0.250000;-4.000000;,
   -6.000000;0.000000;-4.000000;,
   -5.000000;0.000000;-4.000000;,
   -2.513538;0.000000;-4.000000;,
   0.000000;0.000000;-4.000000;,
   2.497847;0.000000;-4.000000;,
   5.000000;0.000000;-4.000000;,
   6.000000;0.000000;-4.000000;,
   8.000000;0.000000;-4.000000;,
   -6.000000;0.250000;-6.000000;,
   -8.000000;0.250000;-6.000000;,
   -6.000000;0.000000;-6.000000;,
   -5.000000;0.000000;-6.000000;,
   -2.513538;0.000000;-6.000000;,
   0.000000;0.000000;-6.000000;,
   2.497847;0.000000;-6.000000;,
   5.000000;0.000000;-6.000000;,
   6.000000;0.000000;-6.000000;,
   8.000000;0.000000;-8.000000;,
   8.000000;0.250000;-8.000000;,
   6.000000;0.250000;-6.000000;,
   -6.000000;0.250000;-8.000000;,
   -8.000000;0.250000;-8.000000;,
   -6.000000;0.000000;-8.000000;,
   -5.000000;0.000000;-8.000000;,
   -2.513538;0.000000;-8.000000;,
   0.000000;0.000000;-8.000000;,
   2.497847;0.000000;-8.000000;,
   5.000000;0.000000;-8.000000;,
   6.000000;0.000000;-8.000000;,
   6.000000;0.250000;-8.000000;,
   -6.000000;0.250000;-15.000002;,
   -8.000000;0.250000;-15.000002;,
   -6.000000;0.000000;-15.000002;,
   -5.000000;0.000000;-15.000002;,
   -2.513538;0.000000;-15.000002;,
   0.000000;0.000000;-15.000002;,
   2.497847;0.000000;-15.000002;,
   5.000000;0.000000;-15.000002;,
   6.000000;0.000000;-15.000002;,
   6.000000;0.250000;-15.000002;,
   8.000000;0.250000;-15.000002;,
   9.464467;0.000000;2.192388;,
   9.464467;0.250000;2.192388;,
   10.878680;0.250000;3.606601;,
   10.523603;0.000000;-0.991115;,
   11.585787;0.000000;0.071068;,
   11.585787;0.250000;0.071068;,
   13.000000;0.250000;1.485281;,
   9.101340;0.000000;-6.656020;,
   10.878680;0.000000;-4.878680;,
   12.644924;0.000000;-3.112435;,
   13.707107;0.000000;-2.050252;,
   13.707107;0.250000;-2.050252;,
   15.121321;0.250000;-0.636039;,
   10.171573;0.250000;-9.828427;,
   8.757360;0.250000;-11.242640;,
   10.171573;0.000000;-9.828427;,
   11.222660;0.000000;-8.777340;,
   13.000000;0.000000;-7.000000;,
   14.766244;0.000000;-5.233756;,
   15.828427;0.000000;-4.171573;,
   15.828427;0.250000;-4.171573;,
   17.242641;0.250000;-2.757359;,
   12.292893;0.250000;-11.949748;,
   10.878679;0.250000;-13.363961;,
   12.292893;0.000000;-11.949748;,
   13.343981;0.000000;-10.898661;,
   15.121321;0.000000;-9.121321;,
   16.887566;0.000000;-7.355076;,
   17.949747;0.000000;-6.292893;,
   17.949747;0.250000;-6.292893;,
   19.363960;0.250000;-4.878680;,
   14.414213;0.250000;-14.071068;,
   13.000000;0.250000;-15.485282;,
   14.414213;0.000000;-14.071068;,
   15.465301;0.000000;-13.019980;,
   17.242641;0.000000;-11.242640;,
   19.008884;0.000000;-9.476397;,
   20.071068;0.000000;-8.414213;,
   20.071068;0.250000;-8.414213;,
   21.485281;0.250000;-7.000000;,
   16.535534;0.250000;-16.192389;,
   15.121321;0.250000;-17.606602;,
   16.535534;0.000000;-16.192389;,
   17.586622;0.000000;-15.141301;,
   19.363962;0.000000;-13.363961;,
   21.130205;0.000000;-11.597717;,
   22.192389;0.000000;-10.535534;,
   22.192389;0.250000;-10.535534;,
   23.606602;0.250000;-9.121321;,
   18.656853;0.250000;-18.313707;,
   17.242640;0.250000;-19.727922;,
   18.656853;0.000000;-18.313707;,
   19.707941;0.000000;-17.262621;,
   21.485281;0.000000;-15.485281;,
   23.251526;0.000000;-13.719036;,
   24.313709;0.000000;-12.656855;,
   24.313709;0.250000;-12.656855;,
   25.727922;0.250000;-11.242640;,
   20.778172;0.250000;-20.435026;,
   19.363958;0.250000;-21.849239;,
   20.778172;0.000000;-20.435026;,
   21.829258;0.000000;-19.383938;,
   23.606598;0.000000;-17.606598;,
   25.372843;0.000000;-15.840354;,
   26.435026;0.000000;-14.778172;,
   26.435026;0.250000;-14.778172;,
   27.849239;0.250000;-13.363957;,
   -6.000000;0.250000;15.000000;,
   -6.000000;0.250000;8.000000;,
   -6.000000;0.000000;15.000000;,
   -6.000000;0.000000;8.000000;,
   6.000000;0.000000;15.000000;,
   6.000000;0.000000;8.000000;,
   6.000000;0.250000;15.000000;,
   6.000000;0.250000;8.000000;,
   -6.000000;0.250000;6.000000;,
   -6.000000;0.000000;6.000000;,
   6.000000;0.000000;5.999999;,
   6.000000;0.250000;5.999999;,
   6.000000;0.250000;5.999999;,
   8.000000;0.250000;4.000000;,
   6.000000;0.000000;5.999999;,
   -6.000000;0.250000;4.000000;,
   -6.000000;0.000000;4.000000;,
   8.000000;0.000000;4.000000;,
   -6.000000;0.250000;2.000000;,
   -6.000000;0.000000;2.000000;,
   -6.000000;0.250000;0.000000;,
   -6.000000;0.000000;0.000000;,
   -6.000000;0.250000;-4.000000;,
   -6.000000;0.000000;-4.000000;,
   -6.000000;0.250000;-6.000000;,
   -6.000000;0.000000;-6.000000;,
   6.000000;0.000000;-6.000000;,
   8.000000;0.000000;-8.000000;,
   -6.000000;0.250000;-8.000000;,
   -6.000000;0.000000;-8.000000;,
   6.000000;0.000000;-6.000000;,
   6.000000;0.250000;-6.000000;,
   6.000000;0.000000;-8.000000;,
   6.000000;0.250000;-6.000000;,
   8.000000;0.250000;-8.000000;,
   6.000000;0.250000;-8.000000;,
   -6.000000;0.250000;-15.000002;,
   -6.000000;0.000000;-15.000002;,
   6.000000;0.000000;-15.000002;,
   6.000000;0.250000;-15.000002;,
   8.000000;0.000000;4.000000;,
   8.000000;0.250000;4.000000;,
   9.464467;0.000000;2.192388;,
   9.464467;0.250000;2.192388;,
   9.464467;0.000000;2.192388;,
   9.464467;0.250000;2.192388;,
   11.585787;0.000000;0.071068;,
   11.585787;0.250000;0.071068;,
   11.585787;0.000000;0.071068;,
   11.585787;0.250000;0.071068;,
   13.707107;0.000000;-2.050252;,
   13.707107;0.250000;-2.050252;,
   8.000000;0.250000;-8.000000;,
   8.000000;0.000000;-8.000000;,
   10.171573;0.250000;-9.828427;,
   10.171573;0.000000;-9.828427;,
   13.707107;0.000000;-2.050252;,
   13.707107;0.250000;-2.050252;,
   15.828427;0.000000;-4.171573;,
   15.828427;0.250000;-4.171573;,
   10.171573;0.250000;-9.828427;,
   10.171573;0.000000;-9.828427;,
   12.292893;0.250000;-11.949748;,
   12.292893;0.000000;-11.949748;,
   15.828427;0.000000;-4.171573;,
   15.828427;0.250000;-4.171573;,
   17.949747;0.000000;-6.292893;,
   17.949747;0.250000;-6.292893;,
   12.292893;0.250000;-11.949748;,
   12.292893;0.000000;-11.949748;,
   14.414213;0.250000;-14.071068;,
   14.414213;0.000000;-14.071068;,
   17.949747;0.000000;-6.292893;,
   17.949747;0.250000;-6.292893;,
   20.071068;0.000000;-8.414213;,
   20.071068;0.250000;-8.414213;,
   14.414213;0.250000;-14.071068;,
   14.414213;0.000000;-14.071068;,
   16.535534;0.250000;-16.192389;,
   16.535534;0.000000;-16.192389;,
   20.071068;0.000000;-8.414213;,
   20.071068;0.250000;-8.414213;,
   22.192389;0.000000;-10.535534;,
   22.192389;0.250000;-10.535534;,
   16.535534;0.250000;-16.192389;,
   16.535534;0.000000;-16.192389;,
   18.656853;0.250000;-18.313707;,
   18.656853;0.000000;-18.313707;,
   22.192389;0.000000;-10.535534;,
   22.192389;0.250000;-10.535534;,
   24.313709;0.000000;-12.656855;,
   24.313709;0.250000;-12.656855;,
   18.656853;0.250000;-18.313707;,
   18.656853;0.000000;-18.313707;,
   20.778172;0.250000;-20.435026;,
   20.778172;0.000000;-20.435026;,
   24.313709;0.000000;-12.656855;,
   24.313709;0.250000;-12.656855;,
   26.435026;0.000000;-14.778172;,
   26.435026;0.250000;-14.778172;;
   153;
   4;3,2,1,0;,
   4;174,5,4,173;,
   4;176,7,6,175;,
   4;7,9,8,6;,
   4;9,11,10,8;,
   4;11,13,12,10;,
   4;13,15,14,12;,
   4;15,17,16,14;,
   4;178,19,18,177;,
   4;180,21,20,179;,
   4;23,22,2,3;,
   4;181,24,5,174;,
   4;182,25,7,176;,
   4;25,26,9,7;,
   4;26,27,11,9;,
   4;27,28,13,11;,
   4;28,29,15,13;,
   4;29,30,17,15;,
   4;183,31,19,178;,
   4;184,32,21,180;,
   4;187,33,186,185;,
   4;35,34,22,23;,
   4;188,36,24,181;,
   4;189,37,25,182;,
   4;37,38,26,25;,
   4;38,39,27,26;,
   4;39,40,28,27;,
   4;40,41,29,28;,
   4;41,42,30,29;,
   3;42,190,30;,
   4;44,43,34,35;,
   4;191,45,36,188;,
   4;192,46,37,189;,
   4;46,47,38,37;,
   4;47,48,39,38;,
   4;48,49,40,39;,
   4;49,50,41,40;,
   4;50,51,42,41;,
   4;51,52,190,42;,
   4;54,53,43,44;,
   4;193,55,45,191;,
   4;194,56,46,192;,
   4;56,57,47,46;,
   4;57,58,48,47;,
   4;58,59,49,48;,
   4;59,60,50,49;,
   4;60,61,51,50;,
   4;61,62,52,51;,
   4;64,63,53,54;,
   4;195,65,55,193;,
   4;196,66,56,194;,
   4;66,67,57,56;,
   4;67,68,58,57;,
   4;68,69,59,58;,
   4;69,70,60,59;,
   4;70,71,61,60;,
   4;71,72,62,61;,
   4;74,73,63,64;,
   4;197,75,65,195;,
   4;198,76,66,196;,
   4;76,77,67,66;,
   4;77,78,68,67;,
   4;78,79,69,68;,
   4;79,80,70,69;,
   4;80,81,71,70;,
   4;81,82,72,71;,
   4;84,83,200,199;,
   4;86,85,73,74;,
   4;201,87,75,197;,
   4;202,88,76,198;,
   4;88,89,77,76;,
   4;89,90,78,77;,
   4;90,91,79,78;,
   4;91,92,80,79;,
   4;92,93,81,80;,
   4;205,94,204,203;,
   3;208,207,206;,
   4;96,95,85,86;,
   4;209,97,87,201;,
   4;210,98,88,202;,
   4;98,99,89,88;,
   4;99,100,90,89;,
   4;100,101,91,90;,
   4;101,102,92,91;,
   4;102,103,93,92;,
   4;211,104,94,205;,
   4;212,105,207,208;,
   3;190,30,52;,
   4;33,186,185,187;,
   4;32,21,180,184;,
   3;106,190,52;,
   4;215,107,214,213;,
   4;216,108,21,32;,
   4;72,109,52,62;,
   4;109,110,106,52;,
   4;219,111,218,217;,
   4;220,112,108,216;,
   3;207,206,208;,
   4;83,200,199,84;,
   4;82,113,72,81;,
   3;113,114,72;,
   4;114,115,109,72;,
   4;115,116,110,109;,
   4;223,117,222,221;,
   4;224,118,112,220;,
   4;120,119,207,208;,
   4;227,121,226,225;,
   4;228,122,113,82;,
   4;122,123,114,113;,
   4;123,124,115,114;,
   4;124,125,116,115;,
   4;231,126,230,229;,
   4;232,127,118,224;,
   4;129,128,119,120;,
   4;235,130,234,233;,
   4;236,131,122,228;,
   4;131,132,123,122;,
   4;132,133,124,123;,
   4;133,134,125,124;,
   4;239,135,238,237;,
   4;240,136,127,232;,
   4;138,137,128,129;,
   4;243,139,242,241;,
   4;244,140,131,236;,
   4;140,141,132,131;,
   4;141,142,133,132;,
   4;142,143,134,133;,
   4;247,144,246,245;,
   4;248,145,136,240;,
   4;147,146,137,138;,
   4;251,148,250,249;,
   4;252,149,140,244;,
   4;149,150,141,140;,
   4;150,151,142,141;,
   4;151,152,143,142;,
   4;255,153,254,253;,
   4;256,154,145,248;,
   4;156,155,146,147;,
   4;259,157,258,257;,
   4;260,158,149,252;,
   4;158,159,150,149;,
   4;159,160,151,150;,
   4;160,161,152,151;,
   4;263,162,262,261;,
   4;264,163,154,256;,
   4;165,164,155,156;,
   4;267,166,266,265;,
   4;268,167,158,260;,
   4;167,168,159,158;,
   4;168,169,160,159;,
   4;169,170,161,160;,
   4;271,171,270,269;,
   4;272,172,163,264;;

   MeshNormals {
    20;
    -1.000000;0.000000;0.000000;,
    -0.777000;0.000000;-0.629500;,
    -0.707107;-0.000000;-0.707107;,
    -0.707107;0.000000;-0.707107;,
    -0.707107;0.000001;-0.707107;,
    -0.707107;-0.000002;-0.707107;,
    -0.707107;0.000001;-0.707107;,
    -0.707107;0.000001;-0.707107;,
    -0.707107;0.000002;-0.707107;,
    -0.707107;0.000002;-0.707107;,
    -0.707107;0.000000;-0.707107;,
    0.000000;1.000000;0.000000;,
    0.644081;-0.000001;0.764957;,
    0.707107;-0.000001;0.707107;,
    0.707107;-0.000000;0.707107;,
    0.707107;0.000000;0.707107;,
    0.707107;0.000001;0.707107;,
    0.707107;0.000001;0.707107;,
    0.707107;0.000002;0.707107;,
    1.000000;0.000000;0.000000;;
    153;
    4;11,11,11,11;,
    4;19,19,19,19;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;0,0,0,0;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;19,19,19,19;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;0,0,0,0;,
    4;11,11,11,11;,
    4;10,10,10,10;,
    4;11,11,11,11;,
    4;19,19,19,19;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    3;11,11,11;,
    4;11,11,11,11;,
    4;19,19,19,19;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;19,19,19,19;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;19,19,19,19;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;19,19,19,19;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;15,15,15,15;,
    4;11,11,11,11;,
    4;19,19,19,19;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;0,0,0,0;,
    3;11,11,11;,
    4;11,11,11,11;,
    4;19,19,19,19;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;0,0,0,0;,
    4;11,11,11,11;,
    3;11,11,11;,
    4;10,10,10,10;,
    4;11,11,11,11;,
    3;11,11,11;,
    4;1,1,1,1;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;4,4,4,4;,
    4;11,11,11,11;,
    3;11,11,11;,
    4;15,15,15,15;,
    4;11,11,11,11;,
    3;11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;3,3,3,3;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;12,12,12,12;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;2,2,2,2;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;16,16,16,16;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;8,8,8,8;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;13,13,13,13;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;9,9,9,9;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;18,18,18,18;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;5,5,5,5;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;17,17,17,17;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;6,6,6,6;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;14,14,14,14;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;11,11,11,11;,
    4;7,7,7,7;,
    4;11,11,11,11;;
   }

   MeshTextureCoords {
    273;
    0.000000;1.000000;,
    0.055789;1.000000;,
    0.055789;0.810037;,
    0.000000;0.810037;,
    0.055789;1.000000;,
    0.055789;0.810037;,
    0.083684;1.000000;,
    0.083684;0.810037;,
    0.153064;1.000000;,
    0.153043;0.810037;,
    0.223157;1.000000;,
    0.223157;0.810037;,
    0.292854;1.000000;,
    0.292833;0.810037;,
    0.362630;1.000000;,
    0.362630;0.810037;,
    0.390524;1.000000;,
    0.390524;0.810037;,
    0.390524;1.000000;,
    0.390524;0.810037;,
    0.446314;1.000000;,
    0.446314;0.810037;,
    0.055789;0.755762;,
    0.000000;0.755762;,
    0.055789;0.755762;,
    0.083684;0.755762;,
    0.153043;0.755762;,
    0.223157;0.755762;,
    0.292833;0.755762;,
    0.362630;0.755762;,
    0.390524;0.755762;,
    0.390524;0.755762;,
    0.446314;0.701486;,
    0.446314;0.701486;,
    0.055789;0.701486;,
    0.000000;0.701486;,
    0.055789;0.701486;,
    0.083684;0.701486;,
    0.153043;0.701486;,
    0.223157;0.701486;,
    0.292833;0.701486;,
    0.362630;0.701486;,
    0.390524;0.701486;,
    0.055789;0.647211;,
    0.000000;0.647211;,
    0.055789;0.647211;,
    0.083684;0.647211;,
    0.153043;0.647211;,
    0.223157;0.647211;,
    0.292833;0.647211;,
    0.362630;0.647211;,
    0.390524;0.647211;,
    0.446314;0.647211;,
    0.055789;0.592936;,
    0.000000;0.592936;,
    0.055789;0.592936;,
    0.083684;0.592936;,
    0.153043;0.592936;,
    0.223157;0.592936;,
    0.292833;0.592936;,
    0.362630;0.592936;,
    0.390524;0.592936;,
    0.446314;0.592936;,
    0.055789;0.484385;,
    0.000000;0.484385;,
    0.055789;0.484385;,
    0.083684;0.484385;,
    0.153043;0.484385;,
    0.223157;0.484385;,
    0.292833;0.484385;,
    0.362630;0.484385;,
    0.390524;0.484385;,
    0.446314;0.484385;,
    0.055789;0.430110;,
    0.000000;0.430110;,
    0.055789;0.430110;,
    0.083684;0.430110;,
    0.153043;0.430110;,
    0.223157;0.430110;,
    0.292833;0.430110;,
    0.362630;0.430110;,
    0.390524;0.430110;,
    0.446314;0.375835;,
    0.446314;0.375835;,
    0.390524;0.430110;,
    0.055789;0.375835;,
    0.000000;0.375835;,
    0.055789;0.375835;,
    0.083684;0.375835;,
    0.153043;0.375835;,
    0.223157;0.375835;,
    0.292833;0.375835;,
    0.362630;0.375835;,
    0.390524;0.375835;,
    0.390524;0.375835;,
    0.055789;0.185872;,
    0.000000;0.185872;,
    0.055789;0.185872;,
    0.083684;0.185872;,
    0.153043;0.185872;,
    0.223157;0.185872;,
    0.292833;0.185872;,
    0.362630;0.185872;,
    0.390524;0.185872;,
    0.390524;0.185872;,
    0.446314;0.185872;,
    0.487164;0.652432;,
    0.487164;0.652432;,
    0.526613;0.690810;,
    0.516708;0.566039;,
    0.546338;0.594865;,
    0.546338;0.594865;,
    0.585786;0.633243;,
    0.477035;0.412308;,
    0.526613;0.460540;,
    0.575882;0.508472;,
    0.605511;0.537297;,
    0.605511;0.537297;,
    0.644960;0.575675;,
    0.506889;0.326216;,
    0.467440;0.287838;,
    0.506889;0.326216;,
    0.536208;0.354740;,
    0.585786;0.402973;,
    0.635055;0.450904;,
    0.664684;0.479729;,
    0.664684;0.479729;,
    0.704133;0.518108;,
    0.566062;0.268648;,
    0.526613;0.230270;,
    0.566062;0.268648;,
    0.595382;0.297172;,
    0.644960;0.345405;,
    0.694229;0.393337;,
    0.723858;0.422162;,
    0.723858;0.422162;,
    0.763307;0.460540;,
    0.625235;0.211081;,
    0.585786;0.172702;,
    0.625235;0.211081;,
    0.654555;0.239605;,
    0.704133;0.287838;,
    0.753402;0.335769;,
    0.783031;0.364594;,
    0.783031;0.364594;,
    0.822480;0.402973;,
    0.684409;0.153513;,
    0.644960;0.115135;,
    0.684409;0.153513;,
    0.713728;0.182037;,
    0.763307;0.230270;,
    0.812575;0.278202;,
    0.842204;0.307027;,
    0.842204;0.307027;,
    0.881653;0.345405;,
    0.743582;0.095946;,
    0.704133;0.057567;,
    0.743582;0.095946;,
    0.772902;0.124470;,
    0.822480;0.172703;,
    0.871749;0.220634;,
    0.901378;0.249459;,
    0.901378;0.249459;,
    0.940827;0.287838;,
    0.802755;0.038378;,
    0.763306;0.000000;,
    0.802755;0.038378;,
    0.832075;0.066902;,
    0.881653;0.115135;,
    0.930922;0.163067;,
    0.960551;0.191892;,
    0.960551;0.191892;,
    1.000000;0.230270;,
    0.055789;1.000000;,
    0.055789;0.810037;,
    0.055789;1.000000;,
    0.055789;0.810037;,
    0.390524;1.000000;,
    0.390524;0.810037;,
    0.390524;1.000000;,
    0.390524;0.810037;,
    0.055789;0.755762;,
    0.055789;0.755762;,
    0.390524;0.755762;,
    0.390524;0.755762;,
    0.390524;0.755762;,
    0.446314;0.701486;,
    0.390524;0.755762;,
    0.055789;0.701486;,
    0.055789;0.701486;,
    0.446314;0.701486;,
    0.055789;0.647211;,
    0.055789;0.647211;,
    0.055789;0.592936;,
    0.055789;0.592936;,
    0.055789;0.484385;,
    0.055789;0.484385;,
    0.055789;0.430110;,
    0.055789;0.430110;,
    0.390524;0.430110;,
    0.446314;0.375835;,
    0.055789;0.375835;,
    0.055789;0.375835;,
    0.390524;0.430110;,
    0.390524;0.430110;,
    0.390524;0.375835;,
    0.390524;0.430110;,
    0.446314;0.375835;,
    0.390524;0.375835;,
    0.055789;0.185872;,
    0.055789;0.185872;,
    0.390524;0.185872;,
    0.390524;0.185872;,
    0.446314;0.701486;,
    0.446314;0.701486;,
    0.487164;0.652432;,
    0.487164;0.652432;,
    0.487164;0.652432;,
    0.487164;0.652432;,
    0.546338;0.594865;,
    0.546338;0.594865;,
    0.546338;0.594865;,
    0.546338;0.594865;,
    0.605511;0.537297;,
    0.605511;0.537297;,
    0.446314;0.375835;,
    0.446314;0.375835;,
    0.506889;0.326216;,
    0.506889;0.326216;,
    0.605511;0.537297;,
    0.605511;0.537297;,
    0.664684;0.479729;,
    0.664684;0.479729;,
    0.506889;0.326216;,
    0.506889;0.326216;,
    0.566062;0.268648;,
    0.566062;0.268648;,
    0.664684;0.479729;,
    0.664684;0.479729;,
    0.723858;0.422162;,
    0.723858;0.422162;,
    0.566062;0.268648;,
    0.566062;0.268648;,
    0.625235;0.211081;,
    0.625235;0.211081;,
    0.723858;0.422162;,
    0.723858;0.422162;,
    0.783031;0.364594;,
    0.783031;0.364594;,
    0.625235;0.211081;,
    0.625235;0.211081;,
    0.684409;0.153513;,
    0.684409;0.153513;,
    0.783031;0.364594;,
    0.783031;0.364594;,
    0.842204;0.307027;,
    0.842204;0.307027;,
    0.684409;0.153513;,
    0.684409;0.153513;,
    0.743582;0.095946;,
    0.743582;0.095946;,
    0.842204;0.307027;,
    0.842204;0.307027;,
    0.901378;0.249459;,
    0.901378;0.249459;,
    0.743582;0.095946;,
    0.743582;0.095946;,
    0.802755;0.038378;,
    0.802755;0.038378;,
    0.901378;0.249459;,
    0.901378;0.249459;,
    0.960551;0.191892;,
    0.960551;0.191892;;
   }

   MeshMaterialList {
    1;
    153;
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
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
      "branchright4lane2way2lane1way.bmp";
     }
    }
   }

   VertexDuplicationIndices {
    273;
    173;
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
    121,
    122,
    123,
    124,
    125,
    126,
    127,
    128,
    129,
    130,
    131,
    132,
    133,
    134,
    135,
    136,
    137,
    138,
    139,
    140,
    141,
    142,
    143,
    144,
    145,
    146,
    147,
    148,
    149,
    150,
    151,
    152,
    153,
    154,
    155,
    156,
    157,
    158,
    159,
    160,
    161,
    162,
    163,
    164,
    165,
    166,
    167,
    168,
    169,
    170,
    171,
    172,
    1,
    2,
    4,
    5,
    16,
    17,
    18,
    19,
    22,
    24,
    30,
    31,
    31,
    32,
    30,
    34,
    36,
    33,
    43,
    45,
    53,
    55,
    63,
    65,
    73,
    75,
    81,
    82,
    85,
    87,
    81,
    84,
    93,
    84,
    83,
    94,
    95,
    97,
    103,
    104,
    33,
    32,
    106,
    107,
    106,
    107,
    110,
    111,
    110,
    111,
    116,
    117,
    83,
    82,
    119,
    121,
    116,
    117,
    125,
    126,
    119,
    121,
    128,
    130,
    125,
    126,
    134,
    135,
    128,
    130,
    137,
    139,
    134,
    135,
    143,
    144,
    137,
    139,
    146,
    148,
    143,
    144,
    152,
    153,
    146,
    148,
    155,
    157,
    152,
    153,
    161,
    162,
    155,
    157,
    164,
    166,
    161,
    162,
    170,
    171;
   }
  }
 }
}

AnimationSet {
 
}