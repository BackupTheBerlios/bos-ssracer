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
   1.000000,0.000000,0.000000,0.000000,0.000000,0.000000,-1.000000,0.000000,0.000000,1.000000,0.000000,0.000000,1.970174,100.000000,14.229036,1.000000;;
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
   179;
   -5.613336;0.250000;14.780604;,
   -3.670931;0.250000;14.304093;,
   -4.292718;0.250000;10.562993;,
   -6.284013;0.250000;10.749389;,
   -3.670931;0.000000;14.304093;,
   -4.292718;0.000000;10.562993;,
   -2.227275;0.000000;13.949936;,
   -2.812725;0.000000;10.424457;,
   0.213879;0.000000;13.351072;,
   -0.310127;0.000000;10.190201;,
   2.639795;0.000000;12.755947;,
   2.176848;0.000000;9.957408;,
   4.098689;0.000000;12.398051;,
   3.672463;0.000000;9.817410;,
   4.098689;0.250000;12.398051;,
   3.672463;0.250000;9.817410;,
   6.041095;0.250000;11.921540;,
   5.663758;0.250000;9.631015;,
   -4.612532;0.250000;7.210934;,
   -6.612369;0.250000;7.236449;,
   -4.612532;0.000000;7.210934;,
   -3.126191;0.000000;7.191969;,
   -0.612857;0.000000;7.159902;,
   1.884786;0.000000;7.128034;,
   3.386817;0.000000;7.108870;,
   3.386817;0.250000;7.108870;,
   5.386654;0.250000;7.083354;,
   -4.689765;0.250000;4.463454;,
   -6.689444;0.250000;4.427586;,
   -4.689765;0.000000;4.463454;,
   -3.203542;0.000000;4.490112;,
   -0.690408;0.000000;4.535190;,
   1.807037;0.000000;4.579987;,
   3.308948;0.000000;4.606926;,
   3.308948;0.250000;4.606926;,
   5.308627;0.250000;4.642794;,
   -4.742510;0.250000;1.619399;,
   -6.739157;0.250000;1.503628;,
   -4.742510;0.000000;1.619399;,
   -3.258540;0.000000;1.705442;,
   -0.749217;0.000000;1.850938;,
   1.744442;0.000000;1.995526;,
   3.244076;0.000000;2.082478;,
   3.244076;0.250000;2.082478;,
   5.240723;0.250000;2.198248;,
   -4.608878;0.250000;-0.685321;,
   -6.605524;0.250000;-0.801090;,
   -4.608878;0.000000;-0.685321;,
   -3.124908;0.000000;-0.599277;,
   -0.615584;0.000000;-0.453781;,
   1.878074;0.000000;-0.309193;,
   3.377708;0.000000;-0.222241;,
   3.377708;0.250000;-0.222241;,
   5.374355;0.250000;-0.106471;,
   -4.475245;0.250000;-2.990039;,
   -6.471891;0.250000;-3.105809;,
   -4.475245;0.000000;-2.990039;,
   -2.991275;0.000000;-2.903996;,
   -0.481952;0.000000;-2.758500;,
   2.011707;0.000000;-2.613912;,
   3.511341;0.000000;-2.526960;,
   3.511341;0.250000;-2.526960;,
   5.507987;0.250000;-2.411190;,
   -4.341612;0.250000;-5.294758;,
   -6.338259;0.250000;-5.410528;,
   -4.341612;0.000000;-5.294758;,
   -2.857643;0.000000;-5.208715;,
   -0.348319;0.000000;-5.063219;,
   2.145339;0.000000;-4.918631;,
   3.644974;0.000000;-4.831679;,
   3.644974;0.250000;-4.831679;,
   5.641620;0.250000;-4.715909;,
   -4.207980;0.250000;-7.599477;,
   -6.204626;0.250000;-7.715247;,
   -4.207980;0.000000;-7.599477;,
   -2.724010;0.000000;-7.513434;,
   -0.214687;0.000000;-7.367938;,
   2.278972;0.000000;-7.223350;,
   3.778606;0.000000;-7.136398;,
   3.778606;0.250000;-7.136398;,
   5.775253;0.250000;-7.020628;,
   -3.988209;0.250000;-10.333859;,
   -5.984856;0.250000;-10.449629;,
   -3.988209;0.000000;-10.333859;,
   -2.504240;0.000000;-10.247815;,
   0.005084;0.000000;-10.102319;,
   2.498742;0.000000;-9.957731;,
   3.998377;0.000000;-9.870780;,
   3.998377;0.250000;-9.870780;,
   5.995023;0.250000;-9.755010;,
   -3.835714;0.250000;-12.640743;,
   -5.835263;0.250000;-12.683201;,
   -3.835714;0.000000;-12.640743;,
   -2.333899;0.000000;-12.608854;,
   0.163385;0.000000;-12.555828;,
   2.676356;0.000000;-12.502469;,
   4.162484;0.000000;-12.470914;,
   4.162484;0.250000;-12.470914;,
   6.162033;0.250000;-12.428457;,
   -3.670931;0.250000;14.304093;,
   -4.292718;0.250000;10.562993;,
   -3.670931;0.000000;14.304093;,
   -4.292718;0.000000;10.562993;,
   4.098689;0.000000;12.398051;,
   3.672463;0.000000;9.817410;,
   4.098689;0.250000;12.398051;,
   3.672463;0.250000;9.817410;,
   -4.292718;0.250000;10.562993;,
   -4.292718;0.000000;10.562993;,
   -4.612532;0.250000;7.210934;,
   -4.612532;0.000000;7.210934;,
   3.672463;0.000000;9.817410;,
   3.672463;0.250000;9.817410;,
   3.386817;0.000000;7.108870;,
   3.386817;0.250000;7.108870;,
   -4.612532;0.250000;7.210934;,
   -4.612532;0.000000;7.210934;,
   -4.689765;0.250000;4.463454;,
   -4.689765;0.000000;4.463454;,
   3.386817;0.000000;7.108870;,
   3.386817;0.250000;7.108870;,
   3.308948;0.000000;4.606926;,
   3.308948;0.250000;4.606926;,
   -4.689765;0.250000;4.463454;,
   -4.689765;0.000000;4.463454;,
   -4.742510;0.250000;1.619399;,
   -4.742510;0.000000;1.619399;,
   3.308948;0.000000;4.606926;,
   3.308948;0.250000;4.606926;,
   3.244076;0.000000;2.082478;,
   3.244076;0.250000;2.082478;,
   -4.742510;0.250000;1.619399;,
   -4.742510;0.000000;1.619399;,
   -4.608878;0.250000;-0.685321;,
   -4.608878;0.000000;-0.685321;,
   3.244076;0.000000;2.082478;,
   3.244076;0.250000;2.082478;,
   3.377708;0.000000;-0.222241;,
   3.377708;0.250000;-0.222241;,
   -4.608878;0.250000;-0.685321;,
   -4.608878;0.000000;-0.685321;,
   -4.475245;0.250000;-2.990039;,
   -4.475245;0.000000;-2.990039;,
   3.377708;0.000000;-0.222241;,
   3.377708;0.250000;-0.222241;,
   3.511341;0.000000;-2.526960;,
   3.511341;0.250000;-2.526960;,
   -4.475245;0.250000;-2.990039;,
   -4.475245;0.000000;-2.990039;,
   -4.341612;0.250000;-5.294758;,
   -4.341612;0.000000;-5.294758;,
   3.511341;0.000000;-2.526960;,
   3.511341;0.250000;-2.526960;,
   3.644974;0.000000;-4.831679;,
   3.644974;0.250000;-4.831679;,
   -4.341612;0.250000;-5.294758;,
   -4.341612;0.000000;-5.294758;,
   -4.207980;0.250000;-7.599477;,
   -4.207980;0.000000;-7.599477;,
   3.644974;0.000000;-4.831679;,
   3.644974;0.250000;-4.831679;,
   3.778606;0.000000;-7.136398;,
   3.778606;0.250000;-7.136398;,
   -4.207980;0.250000;-7.599477;,
   -4.207980;0.000000;-7.599477;,
   -3.988209;0.250000;-10.333859;,
   -3.988209;0.000000;-10.333859;,
   3.778606;0.000000;-7.136398;,
   3.778606;0.250000;-7.136398;,
   3.998377;0.000000;-9.870780;,
   3.998377;0.250000;-9.870780;,
   -3.988209;0.250000;-10.333859;,
   -3.988209;0.000000;-10.333859;,
   -3.835714;0.250000;-12.640743;,
   -3.835714;0.000000;-12.640743;,
   3.998377;0.000000;-9.870780;,
   3.998377;0.250000;-9.870780;,
   4.162484;0.000000;-12.470914;,
   4.162484;0.250000;-12.470914;;
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
   4;109,20,108,107;,
   4;110,21,7,102;,
   4;21,22,9,7;,
   4;22,23,11,9;,
   4;23,24,13,11;,
   4;113,25,112,111;,
   4;114,26,17,106;,
   4;28,27,18,19;,
   4;117,29,116,115;,
   4;118,30,21,110;,
   4;30,31,22,21;,
   4;31,32,23,22;,
   4;32,33,24,23;,
   4;121,34,120,119;,
   4;122,35,26,114;,
   4;37,36,27,28;,
   4;125,38,124,123;,
   4;126,39,30,118;,
   4;39,40,31,30;,
   4;40,41,32,31;,
   4;41,42,33,32;,
   4;129,43,128,127;,
   4;130,44,35,122;,
   4;46,45,36,37;,
   4;133,47,132,131;,
   4;134,48,39,126;,
   4;48,49,40,39;,
   4;49,50,41,40;,
   4;50,51,42,41;,
   4;137,52,136,135;,
   4;138,53,44,130;,
   4;55,54,45,46;,
   4;141,56,140,139;,
   4;142,57,48,134;,
   4;57,58,49,48;,
   4;58,59,50,49;,
   4;59,60,51,50;,
   4;145,61,144,143;,
   4;146,62,53,138;,
   4;64,63,54,55;,
   4;149,65,148,147;,
   4;150,66,57,142;,
   4;66,67,58,57;,
   4;67,68,59,58;,
   4;68,69,60,59;,
   4;153,70,152,151;,
   4;154,71,62,146;,
   4;73,72,63,64;,
   4;157,74,156,155;,
   4;158,75,66,150;,
   4;75,76,67,66;,
   4;76,77,68,67;,
   4;77,78,69,68;,
   4;161,79,160,159;,
   4;162,80,71,154;,
   4;82,81,72,73;,
   4;165,83,164,163;,
   4;166,84,75,158;,
   4;84,85,76,75;,
   4;85,86,77,76;,
   4;86,87,78,77;,
   4;169,88,168,167;,
   4;170,89,80,162;,
   4;91,90,81,82;,
   4;173,92,172,171;,
   4;174,93,84,166;,
   4;93,94,85,84;,
   4;94,95,86,85;,
   4;95,96,87,86;,
   4;177,97,176,175;,
   4;178,98,89,170;;

   MeshNormals {
    21;
    -0.999670;0.000000;0.025689;,
    -0.999516;0.000000;0.031108;,
    -0.998323;-0.000000;-0.057885;,
    -0.998323;-0.000000;-0.057885;,
    -0.998323;0.000000;-0.057885;,
    -0.998323;0.000001;-0.057885;,
    -0.998014;-0.000000;-0.062990;,
    -0.996786;-0.000000;-0.080115;,
    -0.994485;0.000001;0.104880;,
    -0.986633;0.000000;0.162955;,
    0.000000;1.000000;0.000000;,
    0.986468;-0.000000;-0.163955;,
    0.995479;-0.000001;-0.094977;,
    0.996786;-0.000001;0.080115;,
    0.997822;0.000000;0.065960;,
    0.998323;-0.000001;0.057885;,
    0.998323;-0.000000;0.057885;,
    0.998323;0.000000;0.057885;,
    0.998323;0.000000;0.057885;,
    0.999605;0.000000;-0.028099;,
    0.999828;-0.000000;-0.018542;;
    80;
    4;10,10,10,10;,
    4;11,11,11,11;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;9,9,9,9;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;12,12,12,12;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;8,8,8,8;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;19,19,19,19;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;1,1,1,1;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;20,20,20,20;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;0,0,0,0;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;17,17,17,17;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;3,3,3,3;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;15,15,15,15;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;2,2,2,2;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;16,16,16,16;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;4,4,4,4;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;18,18,18,18;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;5,5,5,5;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;13,13,13,13;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;7,7,7,7;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;14,14,14,14;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;10,10,10,10;,
    4;6,6,6,6;,
    4;10,10,10,10;;
   }

   MeshTextureCoords {
    179;
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
    0.200570;0.846154;,
    0.277211;0.846154;,
    0.200570;0.730769;,
    0.277211;0.730769;,
    0.727376;0.846154;,
    0.799615;0.846154;,
    0.727376;0.730769;,
    0.799615;0.730769;,
    0.200570;0.730769;,
    0.277211;0.730769;,
    0.200570;0.615385;,
    0.277211;0.615385;,
    0.727376;0.730769;,
    0.799615;0.730769;,
    0.727376;0.615385;,
    0.799615;0.615385;,
    0.200570;0.615385;,
    0.277211;0.615385;,
    0.200570;0.538462;,
    0.277211;0.538462;,
    0.727376;0.615385;,
    0.799615;0.615385;,
    0.727376;0.538462;,
    0.799615;0.538462;,
    0.200570;0.538462;,
    0.277211;0.538462;,
    0.200570;0.461538;,
    0.277211;0.461538;,
    0.727376;0.538462;,
    0.799615;0.538462;,
    0.727376;0.461538;,
    0.799615;0.461538;,
    0.200570;0.461538;,
    0.277211;0.461538;,
    0.200570;0.384615;,
    0.277211;0.384615;,
    0.727376;0.461538;,
    0.799615;0.461538;,
    0.727376;0.384615;,
    0.799615;0.384615;,
    0.200570;0.384615;,
    0.277211;0.384615;,
    0.200570;0.307692;,
    0.277211;0.307692;,
    0.727376;0.384615;,
    0.799615;0.384615;,
    0.727376;0.307692;,
    0.799615;0.307692;,
    0.200570;0.307692;,
    0.277211;0.307692;,
    0.200570;0.192308;,
    0.277211;0.192308;,
    0.727376;0.307692;,
    0.799615;0.307692;,
    0.727376;0.192308;,
    0.799615;0.192308;,
    0.200570;0.192308;,
    0.277211;0.192308;,
    0.200570;0.076923;,
    0.277211;0.076923;,
    0.727376;0.192308;,
    0.799615;0.192308;,
    0.727376;0.076923;,
    0.799615;0.076923;,
    0.200570;0.076923;,
    0.277211;0.076923;,
    0.200570;-0.003440;,
    0.277211;-0.003440;,
    0.727376;0.076923;,
    0.799615;0.076923;,
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
    179;
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
    2,
    5,
    18,
    20,
    13,
    15,
    24,
    25,
    18,
    20,
    27,
    29,
    24,
    25,
    33,
    34,
    27,
    29,
    36,
    38,
    33,
    34,
    42,
    43,
    36,
    38,
    45,
    47,
    42,
    43,
    51,
    52,
    45,
    47,
    54,
    56,
    51,
    52,
    60,
    61,
    54,
    56,
    63,
    65,
    60,
    61,
    69,
    70,
    63,
    65,
    72,
    74,
    69,
    70,
    78,
    79,
    72,
    74,
    81,
    83,
    78,
    79,
    87,
    88,
    81,
    83,
    90,
    92,
    87,
    88,
    96,
    97;
   }
  }
 }
}

AnimationSet {
 
}