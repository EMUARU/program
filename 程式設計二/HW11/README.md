# HW11：ATM 系統（拆分交易類別）

> 延續 HW10，將查詢餘額、提款、存款分別設計為 `BalanceInquiry`、`Withdrawal`、`Deposit` 類別；帳戶資料以 `vector<Account>` 管理。

| 檔案 | 說明 |
|---|---|
| `Account.h`／`.cpp` | 帳戶：帳號、PIN、可用餘額與總餘額 |
| `BalanceInquiry.h`／`.cpp` | 查詢餘額 |
| `Withdrawal.h`／`.cpp` | 提款 |
| `Deposit.h`／`.cpp` | 存款 |
| `Assignment 11.cpp` | 主程式：登入驗證與交易選單 |

測試帳號：帳號 `12345`／PIN `54321`，或帳號 `98765`／PIN `56789`。
