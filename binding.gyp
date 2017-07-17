{
  "targets": [
    {
      "target_name": "cics-exci-bindings",
      "sources": [ "cics-exci.cc" ],
      "link_settings": {
        "libraries": ["-L<(module_root_dir)/libraries/", "-lCicsExci64Connector"],
      },
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "<(module_root_dir)/includes/"
      ]
    },
    {
      "target_name": "action_after_build",
      "type": "none",
      "dependencies": [ "<(module_name)" ],
      "copies": [
        {
          "files": [ "<(PRODUCT_DIR)/<(module_name).node" ],
          "destination": "<(module_path)"
        }
      ]
    }
  ]
}
