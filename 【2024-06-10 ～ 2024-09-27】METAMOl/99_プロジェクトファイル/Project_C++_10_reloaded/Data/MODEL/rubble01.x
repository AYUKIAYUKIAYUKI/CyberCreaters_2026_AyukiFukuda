xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 18;
 1.18836;0.93713;-2.72010;,
 2.44950;1.73903;0.02073;,
 2.40878;-1.08681;0.06247;,
 0.28653;-2.46563;-3.08019;,
 0.03929;0.77377;3.08019;,
 0.48718;-2.81985;2.88893;,
 -2.44950;1.31178;0.72549;,
 -2.11510;-1.17643;0.02073;,
 1.18836;0.93713;-2.72010;,
 0.28653;-2.46563;-3.08019;,
 -0.30503;3.53411;1.75750;,
 -0.30503;3.53411;1.75750;,
 -0.30503;3.53411;1.75750;,
 -0.30503;3.53411;1.75750;,
 0.38884;-3.53411;0.02073;,
 0.38884;-3.53411;0.02073;,
 0.38884;-3.53411;0.02073;,
 0.38884;-3.53411;0.02073;;
 
 12;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 3;10,1,0;,
 3;11,4,1;,
 3;12,6,4;,
 3;13,8,6;,
 3;14,3,2;,
 3;15,2,5;,
 3;16,5,7;,
 3;17,7,9;;
 
 MeshMaterialList {
  1;
  12;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   1.000000;1.000000;1.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   1.000000;1.000000;1.000000;;
   TextureFilename {
    "Data\\TEXTURE\\destructible.jpg";
   }
  }
 }
 MeshNormals {
  18;
  -0.077361;0.851027;-0.519392;,
  0.883884;-0.096273;-0.457691;,
  0.741494;0.215798;0.635310;,
  -0.703598;0.033028;0.709830;,
  0.854269;-0.372131;-0.362964;,
  0.854527;-0.479052;-0.200730;,
  0.854326;-0.328144;0.403050;,
  -0.765023;-0.601159;0.230969;,
  0.770566;-0.635087;-0.053792;,
  0.795980;0.033400;0.604401;,
  -0.746819;-0.488719;0.451016;,
  -0.600709;0.461479;-0.652829;,
  -0.695321;0.186816;-0.693995;,
  0.312609;0.863217;-0.396398;,
  0.659429;0.390170;0.642589;,
  -0.630252;0.270162;0.727870;,
  -0.685480;-0.728005;-0.011192;,
  -0.668335;-0.709797;-0.222522;;
  12;
  4;1,1,5,4;,
  4;2,2,6,9;,
  4;3,3,7,10;,
  4;11,11,12,12;,
  3;0,13,13;,
  3;14,2,2;,
  3;15,3,3;,
  3;0,11,11;,
  3;8,4,5;,
  3;8,5,6;,
  3;16,10,7;,
  3;16,7,17;;
 }
 MeshTextureCoords {
  18;
  0.000000;0.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.000000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.125000;0.000000;,
  0.375000;0.000000;,
  0.625000;0.000000;,
  0.875000;0.000000;,
  0.125000;1.000000;,
  0.375000;1.000000;,
  0.625000;1.000000;,
  0.875000;1.000000;;
 }
}
