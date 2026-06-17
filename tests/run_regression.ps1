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

    function Run-Case {
        param(
            [string]$Name,
            [string]$InputText,
            [string]$ExpectedText
        )

        $exe = if (Test-Path .\library.exe) { '.\library.exe' } else { '.\library' }
        $args = @((Join-Path $tmpDir 'books.txt'), (Join-Path $tmpDir 'user.txt'), (Join-Path $tmpDir 'loan.txt'))

        $output = $InputText | & $exe @args 2>&1 | Out-String

        if ($output -notmatch [regex]::Escape($ExpectedText)) {
            Write-Host "[FAIL] $Name"
            Write-Host "Expected to find: $ExpectedText"
            Write-Host "--- Output ---"
            Write-Host $output
            exit 1
        }

        Write-Host "[PASS] $Name"
    }

    Run-Case -Name 'quit_from_main_menu' -InputText "5`n" -ExpectedText 'Goodbye'
    Run-Case -Name 'show_books_then_quit' -InputText "4`n5`n" -ExpectedText 'Programming in C'
    Run-Case -Name 'invalid_option_then_quit' -InputText "x`n5`n" -ExpectedText 'invalid'
    Run-Case -Name 'login_failure_then_quit' -InputText "2`nno_user`nbad_pass`n5`n" -ExpectedText 'invalid'
    Run-Case -Name 'librarian_login_then_quit' -InputText "2`nadmin`nadmin123`n5`n5`n" -ExpectedText 'Successfully logged in as Librarian'

    Copy-Item (Join-Path $tmpDir 'loan.txt') (Join-Path $tmpDir 'loan_before.txt') -Force
    $exe = if (Test-Path .\library.exe) { '.\library.exe' } else { '.\library' }
    $args = @((Join-Path $tmpDir 'books.txt'), (Join-Path $tmpDir 'user.txt'), (Join-Path $tmpDir 'loan.txt'))
    $borrowReturnOutput = "2`nalice`nalice123`n1`n1`n2`n1`n5`n5`n" | & $exe @args 2>&1 | Out-String

    if ($borrowReturnOutput -notmatch 'successfuly borrowed') {
        Write-Host '[FAIL] borrow_and_return_flow'
        Write-Host 'Expected borrow success message'
        Write-Host '--- Output ---'
        Write-Host $borrowReturnOutput
        exit 1
    }

    if ($borrowReturnOutput -notmatch 'successfully returned') {
        Write-Host '[FAIL] borrow_and_return_flow'
        Write-Host 'Expected return success message'
        Write-Host '--- Output ---'
        Write-Host $borrowReturnOutput
        exit 1
    }

    $beforeLoan = Get-Content (Join-Path $tmpDir 'loan_before.txt') -Raw
    $afterLoan = Get-Content (Join-Path $tmpDir 'loan.txt') -Raw
    if ($beforeLoan -ne $afterLoan) {
        Write-Host '[FAIL] borrow_and_return_flow'
        Write-Host 'Loan file was not restored after borrow+return cycle'
        Write-Host '--- Before ---'
        Write-Host $beforeLoan
        Write-Host '--- After ---'
        Write-Host $afterLoan
        exit 1
    }

    Write-Host '[PASS] borrow_and_return_flow'

    Write-Host 'All regression tests passed.'
}
finally {
    if (Test-Path $tmpDir) {
        Remove-Item -Path $tmpDir -Recurse -Force
    }
}
