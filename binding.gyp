{
    "conditions": [
        ['OS=="win"', {
            "targets": [
                {
                    "target_name": "rinku_native_addons_win32",
                    "sources": ["lib/windows.cc"]
                }
            ]
        }]
    ]
}