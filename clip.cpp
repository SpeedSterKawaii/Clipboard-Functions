static int SetClipboard(lua_State* LS) {
		const char* str = lua_tostring(LS, -1);
		int len = strlen(str);
		HGLOBAL hMem = GlobalAlloc(GMEM_MOVEABLE, len + 1);
		void* mem_ptr = GlobalLock(hMem);
		memcpy(mem_ptr, str, len + 1);
		GlobalUnlock(hMem);
		OpenClipboard(NULL);
		EmptyClipboard();
		SetClipboardData(CF_TEXT, hMem);
		CloseClipboard();
		return 0;
	}

	static int GetClipboard(lua_State* L)
	{
		std::size_t Length;
		const char* Setting = lua_tolstring(L, 1, &Length);
		if (OpenClipboard(NULL))
		{
			HANDLE Got = GetClipboardData(CF_TEXT);
			if (Got == nullptr)
			{
				CloseClipboard();
			}

			char* pszText = static_cast<char*>(GlobalLock(Got));
			if (pszText == nullptr)
			{
				CloseClipboard();
			}
			std::string text(pszText);
			GlobalUnlock(Got);
			CloseClipboard();
			lua_pushstring(L, text.c_str());
			return 1;
		}
	}
