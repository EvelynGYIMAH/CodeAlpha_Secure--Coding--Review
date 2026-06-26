[README.md](https://github.com/user-attachments/files/29381146/README.md)

# Cyber Security Task 3: Secure Coding Review
Company: CodeAlpha  
Intern Name:EVELYN OSEI GYIMAH
Domain: Cyber Security  



## Project Overview
This project fulfills TASK 3: Secure Coding Review from the "Cyber Security Tasks & Instructions — CodeAlpha M1.pdf" curriculum[span_0](start_span)[span_0](end_span). The objective is to perform a hybrid security audit (combining manual static code inspection with automated tools) on a C-based user authentication module. The repository documents identified vulnerabilities, maps their operational risks, and provides a fully remediated, secure implementation.

### Repository Structure
* `vulnerable.c`: The unsecure source code featuring standard structural vulnerabilities.
* `secure.c`: The hardened source code written using length-bounded functions.
* `README.md`: The complete technical audit report and Static Application Security Testing (SAST) logs.



# Technical Audit & Vulnerability Report

1. Manual Code Inspection Findings
During manual analysis of `vulnerable.c`, three distinct architectural flaws were identified:

Finding A: Buffer Overflow via `gets()`
* Severity: Critical  
* Location: `login_system()` function  
* Description:The program utilizes the legacy `gets()` function to capture input. Because `gets()` lacks inherent boundary checking, input exceeding the allocated 16-byte stack array (`user_password`) overflows directly into adjacent memory blocks.
* Impact: Arbitrary code execution, stack corruption, or immediate application crash.

 Finding B: Buffer Overflow via Unbounded `strcat()`
* Severity: High  
* Description: String manipulation utilizes `strcpy` and `strcat` to format system logs. Because the static buffer `log_message` is constrained to 100 bytes, appending an unvalidated `user_password` array can overwrite boundary lines.
* Impact:System memory contamination and exploitation of local memory space.

Finding C: Insecure Information Storage
*Severity:Medium  
* Description:Administrative passwords (`AdminSecret123`) and definitive local file paths (`/var/log/secure_app.log`) are hardcoded directly into the script execution lines.
* Impact: Reverse-engineering the binary target easily yields raw strings and administrative credentials.

---

## 2. Automated SAST Log via Flawfinder
Automated scanning using **Flawfinder** flags the specific risk densities of the outdated string handlers:

```text
vulnerable.c:11:  [5] (buffer) gets:
  Does not check for buffer overflows when reading to a string. Risk is high. 
  Remediation: Use fgets instead.

vulnerable.c:19:  [3] (buffer) strcpy:
  Does not check for buffer overflows when copying strings. Risk is medium.
  Remediation: Consider using snprintf instead.

vulnerable.c:20:  [3] (buffer) strcat:
  Does not check for buffer overflows when concatenating strings. Risk is medium.
  Remediation: Consider using snprintf instead.

ANALYSIS SUMMARY:
Hits = 3 | Lines Scanned = 31 | High Risk Hits = 1
