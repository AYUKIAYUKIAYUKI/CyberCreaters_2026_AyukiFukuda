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
 15;
 -0.55531;2.26804;-1.72132;,
 -2.56194;1.90153;2.96316;,
 2.56194;2.17559;2.73105;,
 1.12801;2.39163;-0.97723;,
 -0.49409;-2.31931;0.86969;,
 2.02067;-1.70760;0.58317;,
 1.12801;2.39163;-0.97723;,
 2.56194;2.17559;2.73105;,
 1.71435;-1.77721;-2.10532;,
 -0.55531;2.26804;-1.72132;,
 1.12801;2.39163;-0.97723;,
 2.02067;-1.70760;0.58317;,
 -2.56194;1.90153;2.96316;,
 -0.82006;-2.39163;-2.96316;,
 -0.82006;-2.39163;-2.96316;;
 
 6;
 4;0,1,2,3;,
 4;4,5,6,7;,
 4;8,9,10,11;,
 4;4,7,12,13;,
 4;8,14,12,9;,
 4;4,14,8,11;;
 
 MeshMaterialList {
  1;
  6;
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
  7;
  -0.070091;0.995840;0.058223;,
  0.634981;-0.743460;0.209920;,
  0.774847;0.264364;-0.574216;,
  -0.521986;-0.570309;0.634254;,
  0.871268;-0.324918;0.367860;,
  -0.429661;0.255251;-0.866163;,
  0.236167;-0.971711;-0.001749;;
  6;
  4;0,0,0,0;,
  4;1,1,4,4;,
  4;2,2,2,2;,
  4;3,3,3,3;,
  4;5,5,5,5;,
  4;1,6,6,1;;
 }
 MeshTextureCoords {
  15;
  0.770470;1.000000;,
  0.485490;0.547610;,
  1.000000;0.547610;,
  1.000000;1.000000;,
  0.082000;0.375750;,
  0.000000;0.345170;,
  0.000000;0.000000;,
  0.452390;0.000000;,
  0.912330;0.348650;,
  0.770470;0.000000;,
  1.000000;0.000000;,
  1.000000;0.345170;,
  0.501380;0.000000;,
  0.122300;0.379370;,
  0.878180;0.379370;;
 }
}
