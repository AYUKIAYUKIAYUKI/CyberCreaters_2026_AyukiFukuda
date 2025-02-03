//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_	// 二重インクルード防止

//****************************************************
// サウンドクラス
//****************************************************
class CSound final
{
public:

	//****************************************************
	// サウンド一覧
	//****************************************************
	enum class LABEL
	{
		BGM = 0,		// オープニング
		DISPLAY,		// 表示音
		SELECT,			// 選択音
		DEFINE,			// 決定音
		EXPLOSION,		// 爆発音
		METAMORPHOSE,	// 変身音
		TWINKLING,		// きらきら音
		STOP,			// 衝突音
		BOUND,			// バウンド音
		BREAK,			// 破壊音
		DIE,			// 死亡音
		SHOT,			// 発射音
		MISS,			// ミス音
		GOAL,			// ゴール音
		GET,			// 取得音
		CHARGE,			// チャージ音
		RUSH,			// 突進音
		MAX,
	};

	HRESULT Init(HWND hWnd);		// 初期設定
	void Release();					// 解放
	HRESULT Play(LABEL label);		// 再生
	void Stop(LABEL label);			// 停止 (選択)
	void Stop();					// 停止 (全て)
	void SetVol(LABEL label);		// 音量を設定
	float GetVol(LABEL label);		// 音量を取得

	static CSound* GetInstance();	// サウンドを取得

private:

	//****************************************************
	// サウンド情報の構造体
	//****************************************************
	struct SOUNDINFO
	{
		const char* pFilename;	// ファイル名
		int nCntLoop;			// ループカウント
		float fVolume;			// 音量
	};

	CSound();	// コンストラクタ
	~CSound();	// デストラクタ

	void Create();																					// 生成
	void Uninit();																					// 終了処理
	HRESULT CheckChunk(HANDLE hFile, DWORD format, DWORD* pChunkSize, DWORD* pChunkDataPosition);	// チャンクのチェック
	HRESULT ReadChunkData(HANDLE hFile, void* pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);	// チャンクデータの読み込み

	IXAudio2* m_pXAudio2;												// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice* m_pMasteringVoice;							// マスターボイス
	IXAudio2SourceVoice* m_apSourceVoice[static_cast<int>(LABEL::MAX)];	// ソースボイス
	BYTE* m_apDataAudio[static_cast<int>(LABEL::MAX)];					// オーディオデータ
	DWORD m_aSizeAudio[static_cast<int>(LABEL::MAX)];					// オーディオデータサイズ
	SOUNDINFO m_aSoundInfo[static_cast<int>(LABEL::MAX)];				// サウンド情報 (仮)

	static CSound* m_pSound;	// サウンド
};

#endif	// _SOUND_H_
