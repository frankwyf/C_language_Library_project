$ErrorActionPreference = 'Stop'

$root = Split-Path -Parent $PSScriptRoot
Set-Location $root

if (-not (Test-Path .\library.exe) -and -not (Test-Path .\library)) {
    mingw32-make
}

$tmpDir = Join-Path $env:TEMP ("library-regression-" + [guid]::NewGuid().ToString('N'))
New-Item -ItemType Directory -Path $tmpDir | Out-Null

try {
    Copy-Item books.txt (Join-Path $tmpDir 'books.txt') -Force
    Copy-Item user.txt (Join-Path $tmpDir 'user.txt') -Force
    Copy-Item loan.txt (Join-Path $tmpDir 'loan.txt') -Force

    $exe = if (Test-Path .\library) { '.\library' } else { '.\library.exe' }
    $booksPath = Join-Path $tmpDir 'books.txt'
    $usersPath = Join-Path $tmpDir 'user.txt'
    $loanPath = Join-Path $tmpDir 'loan.txt'

    $out1 = "5`n" | & $exe $booksPath $usersPath $loanPath 2>&1 | Out-String
    if ($out1 -notmatch [regex]::Escape('Goodbye')) { throw '[FAIL] quit_from_main_menu' }
    Write-Host '[PASS] quit_from_main_menu'

    $out2 = "4`n5`n" | & $exe $booksPath $usersPath $loanPath 2>&1 | Out-String
    if ($out2 -notmatch [regex]::Escape('Programming in C')) { throw '[FAIL] show_books_then_quit' }
    Write-Host '[PASS] show_books_then_quit'

    $out3 = "x`n5`n" | & $exe $booksPath $usersPath $loanPath 2>&1 | Out-String
    if ($out3 -notmatch [regex]::Escape('invalid')) { throw '[FAIL] invalid_option_then_quit' }
    Write-Host '[PASS] invalid_option_then_quit'

    $out4 = "2`nno_user`nbad_pass`n5`n" | & $exe $booksPath $usersPath $loanPath 2>&1 | Out-String
    if ($out4 -notmatch [regex]::Escape('invalid')) { throw '[FAIL] login_failure_then_quit' }
    Write-Host '[PASS] login_failure_then_quit'

    $out5 = "2`nadmin`nadmin123`n5`n5`n" | & $exe $booksPath $usersPath $loanPath 2>&1 | Out-String
    if ($out5 -notmatch [regex]::Escape('Successfully logged in as Librarian')) { throw '[FAIL] librarian_login_then_quit' }
    Write-Host '[PASS] librarian_login_then_quit'

    $out6 = "1`nCaseUser`nregcase`nregpass`n2`nregcase`nregpass`n5`n5`n" | & $exe $booksPath $usersPath $loanPath 2>&1 | Out-String
    if ($out6 -notmatch [regex]::Escape('registered successfully')) { throw '[FAIL] register_then_login' }
    Write-Host '[PASS] register_then_login'

    Copy-Item $loanPath (Join-Path $tmpDir 'loan_before.txt') -Force
    Copy-Item $booksPath (Join-Path $tmpDir 'books_before_borrow_return.txt') -Force

    $out7 = "2`nalice`nalice123`n1`n1`n2`n1`n5`n5`n" | & $exe $booksPath $usersPath $loanPath 2>&1 | Out-String
    if ($out7 -notmatch 'successfuly borrowed') { throw '[FAIL] borrow_and_return_flow borrow message' }
    if ($out7 -notmatch 'successfully returned') { throw '[FAIL] borrow_and_return_flow return message' }

    $beforeLoan = Get-Content (Join-Path $tmpDir 'loan_before.txt') -Raw
    $afterLoan = Get-Content $loanPath -Raw
    if ($beforeLoan -ne $afterLoan) { throw '[FAIL] borrow_and_return_flow loan rollback' }

    $beforeBooksBorrowReturn = Get-Content (Join-Path $tmpDir 'books_before_borrow_return.txt') -Raw
    $afterBooksBorrowReturn = Get-Content $booksPath -Raw
    if ($beforeBooksBorrowReturn -ne $afterBooksBorrowReturn) { throw '[FAIL] borrow_and_return_flow books rollback' }
    Write-Host '[PASS] borrow_and_return_flow'

    Copy-Item $booksPath (Join-Path $tmpDir 'books_before_admin.txt') -Force
    $out8 = "2`nadmin`nadmin123`n1`nRegression Title`nRegression Author`n2020`n1`n2`n14`n5`n5`n" | & $exe $booksPath $usersPath $loanPath 2>&1 | Out-String
    if ($out8 -notmatch 'successfuly added') { throw '[FAIL] admin_add_remove_flow add message' }
    if ($out8 -notmatch 'removed successfuly') { throw '[FAIL] admin_add_remove_flow remove message' }

    $beforeBooksAdmin = Get-Content (Join-Path $tmpDir 'books_before_admin.txt') -Raw
    $afterBooksAdmin = Get-Content $booksPath -Raw
    if ($beforeBooksAdmin -ne $afterBooksAdmin) { throw '[FAIL] admin_add_remove_flow books rollback' }
    Write-Host '[PASS] admin_add_remove_flow'

    Write-Host 'All regression tests passed.'
}
finally {
    if (Test-Path $tmpDir) {
        Remove-Item -Path $tmpDir -Recurse -Force
    }
}
