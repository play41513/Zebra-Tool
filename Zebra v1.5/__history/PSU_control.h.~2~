//---------------------------------------------------------------------------

#ifndef PSU_controlH
#define PSU_controlH


#define TEST_END			0
#define RS232_WRITE			1
#define RS232_READ			2
#define TEST_PASS			3
#define TEST_FAIL			4
#define TEST_OCP			5
#define PSU_NO_RESPOND		6

//---------------------------------------------------------------------------
struct tag_cmd_desc {
	char *cmd;
	int (*pfn)(char *s);
	};
	typedef struct tag_cmd_desc CMD_DESC;
class cPSU{
	private:


	public:


		bool 	open_psu_com();
		int 	PSU_CMD_Test(bool bOVP);
		void 	search_Reg_ComNum();
		void 	SearchPSUCOM();

		void 	QueueClear();
		void 	PSU_Stop();

};
#endif
