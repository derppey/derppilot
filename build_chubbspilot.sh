#!/bin/bash

set -x

# Function to determine the local network range
get_network_range() {
    local ip
    ip=$(ipconfig getifaddr en0 2>/dev/null || ip addr show | grep 'inet ' | grep -v '127.0.0.1' | awk '{print $2}' | cut -d/ -f1 | head -n1)
    if [[ -z "$ip" ]]; then
        echo "ERROR: Unable to determine local IP address."
        exit 1
    fi
    # Convert IP to subnet (e.g., 192.168.1.0/24)
    local subnet
    subnet=$(echo "$ip" | awk -F. '{print $1 "." $2 "." $3 ".0/24"}')
    echo "$subnet"
}

# Function to detect device IP using nmap
get_device_ip_nmap() {
    local network_range
    network_range=$(get_network_range)
    echo "Scanning network range: $network_range"
    # Scan for devices with SSH ports 22 or 8022 open
    nmap -p 22,8022 --open -oG - "$network_range" | awk '/22\/open|8022\/open/{print $2}'
}

# Automatically detect DEVICE_IP
detect_device_ip() {
    local possible_ips
    possible_ips=$(get_device_ip_nmap)
    local device_ip=""
    for ip in $possible_ips; do
        if ssh -o ConnectTimeout=2 -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null "$DEVICE_USER@$ip" 'exit' 2>/dev/null; then
            device_ip="$ip"
            break
        fi
    done

    if [[ -z "$device_ip" ]]; then
        echo "ERROR: Failed to detect device IP via nmap."
        exit 1
    fi

    echo "$device_ip"
}

# Configuration
DEVICE_USER="comma"
DEVICE_IP=$(detect_device_ip)

# Remove existing SSH keys for DEVICE_IP
ssh-keygen -R "$DEVICE_IP" > /dev/null 2>&1

echo "Detected Device IP: $DEVICE_IP"

# Function to get the current git branch on the SSH device
get_device_branch() {
    ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null "$DEVICE_USER@$DEVICE_IP" 'cd /data/openpilot && git rev-parse --abbrev-ref HEAD'
}

# Function to check if prebuilt exists
check_prebuilt() {
    # Check for the 'prebuilt' file
    PREBUILT_FILE=$(ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null "$DEVICE_USER@$DEVICE_IP" 'test -f /data/openpilot/prebuilt && echo "yes" || echo "no"')

    # Additionally, check if any .so files exist as an indicator
    ESSENTIAL=$(ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null "$DEVICE_USER@$DEVICE_IP" 'find /data/openpilot -type f -name "*.so" | grep -q . && echo "yes" || echo "no"')

    if [[ "$PREBUILT_FILE" == "yes" || "$ESSENTIAL_SO" == "yes" ]]; then
        echo "yes"
    else
        echo "no"
    fi
}

# Function to skip compilation and clean
skip_compile_device() {
    echo "Proceeding without recompilation..." >&2  # Redirect to stderr
    OUTPUT=$(ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null "$DEVICE_USER@$DEVICE_IP" << 'ENDSSH'
        set -e
        set -x
        cd /data/openpilot

        # Add compiled files
        git add -f .
        git commit -m "compile" --allow-empty

        # Delete specified files
        find . -type f \( \
            -name '*.a' -o \
            -name '*.o' -o \
            -name '*.os' -o \
            -name '*.pyc' -o \
            -name 'moc_*' -o \
            -name '*.cc' -o \
            -name '**.github' -o \
            -name '**.idea' -o \
            -name '**.run' -o \
            -path '**/docs' -o \
            -name 'Jenkinsfile' -o \
            -name 'supercombo.onnx' -o \
            -path '**/panda/certs/' -o \
            -path '**/panda/crypto/' -o \
            -path '**/panda/docs/' -o \
            -path '**/panda/drivers/' -o \
            -path '**/panda/release/' -o \
            -path '**/panda/tests/' -o \
            -path '**/panda/examples/' -o \
            -path '**/panda/.github/' -o \
            -path '**/release/' -o \
            -path '**/.github/' -o \
            -path '**/selfdrive/ui/replay/' -o \
            -path '**/__pycache__/' -o \
            -path '**/selfdrive/ui/qt/offroad/chubbs/' -o \
            -path '${{env.SCONS_CACHE_DIR}}' -o \
            -path '**/.git/' -o \
            -name 'SConstruct' -o \
            -name 'SConscript' -o \
            -path '**/.venv/' -o \
            -path './venv/' -o \
            -path './.venv/' -o \
            -path './.ci_cache/' -o \
            -path './.env/' -o \
            -name '.clang-format' -o \
            -name '.DS_Store' -o \
            -name '.tags' -o \
            -path '**/.ipynb_checkpoints/' -o \
            -path '**/.idea/' -o \
            -path '**/.overlay_init/' -o \
            -path '**/.overlay_consistent/' -o \
            -name 'model2.png' -o \
            -name 'a.out' -o \
            -path '**/.hypothesis/' \
        \) ! \( \
            -path '**/panda/board/' -o \
            -path '**/panda/board/obj' -o \
            -path '**/panda/board/obj/panda.bin.signed' -o \
            -path '**/panda/board/obj/panda_h7.bin.signed' -o \
            -path '**/panda/board/obj/bootstub.panda.bin' -o \
            -path '**/panda/board/obj/bootstub.panda_h7.bin' \
        \) -delete

        # Remove build system artifacts
        rm -rf .sconsign.dblite Jenkinsfile release/

        # Remove generated directories
        rm -rf cereal/gen/cpp

        # Remove remaining MPC-generated files
        rm -rf selfdrive/controls/lib/longitudinal_mpc_lib/c_generated_code/main_*
        rm -rf selfdrive/controls/lib/lateral_mpc_lib/c_generated_code/main_*

        # Additional Deletions
        # Remove specific directories except .github/workflows and delete body/
        find .github -mindepth 1 ! -path './.github/workflows*' -delete
        rm -rf .vscode .devcontainer debug 

        # Remove Docker-related files
        rm -f Dockerfile* .dockerignore

        # Remove test files and directories
        find . -type f -iname '*test*' -delete
        find . -type d -iname '*test*' -exec rm -rf {} +

        # Remove all files named LICENSE (case-insensitive)
        find . -type f -iname 'license*' -delete

        # Remove configuration files
        rm -f .clang-tidy .editorconfig

        # Remove debug-related files and directories
        find . -type f -iname '*debug*' -delete
        find . -type d -iname '*debug*' -exec rm -rf {} +

        touch prebuilt

        # Amend with cleaned state
        git add -f .
        git commit --amend -m "Prebuilt" --allow-empty

        # Output hash
        echo "HASH=$(git rev-parse HEAD)"
ENDSSH
    )
    set -x  # Re-enable debug mode

    SSH_STATUS=$?
    if [ $SSH_STATUS -ne 0 ]; then
        echo "ERROR: Commit and clean SSH session failed with status $SSH_STATUS" >&2
        echo "Output was:" >&2
        echo "$OUTPUT" >&2
        exit 1
    fi

    # Extract hash
    COMMIT_HASH=$(echo "$OUTPUT" | grep "^HASH=" | cut -d= -f2)

    if ! [[ $COMMIT_HASH =~ ^[0-9a-f]{40}$ ]]; then
        echo "ERROR: Invalid commit hash: $COMMIT_HASH" >&2
        echo "Full output was:" >&2
        echo "$OUTPUT" >&2
        exit 1
    fi

    echo "$COMMIT_HASH"
}

# Function to handle workspace operations
workspace_operations() {
    local device_commit=$1
    echo "=== Starting workspace operations ==="
    export GIT_SSH_COMMAND="ssh -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null"

    # Setup remote if needed
    if ! git remote | grep -q "device"; then
        git remote add device ssh://"${DEVICE_USER}"@"${DEVICE_IP}":/data/openpilot
    fi

    # Remove conflicting files before cherry-pick
    rm -f panda/tests/hitl/known_bootstub/bootstub.panda_h7.bin \
          panda/tests/hitl/known_bootstub/bootstub_f4_first_dos_production.panda.bin \
          panda/tests/hitl/known_bootstub/bootstub_f4_only_bcd.panda.bin \
          selfdrive/pandad/tests/bootstub.panda.bin \
          selfdrive/pandad/tests/bootstub.panda_h7.bin \
          selfdrive/pandad/tests/bootstub.panda_h7_spiv0.bin \
          third_party/libyuv/larch64/lib/libyuv.a \
          third_party/libyuv/x86_64/lib/libyuv.a \
          tinygrad_repo/test/models/waifu2x/input.png \
          tinygrad_repo/test/models/waifu2x/output.png \
          tinygrad_repo/test/models/whisper/test.wav \
          tools/cabana/assets/cabana-icon.png

    # Setup Git LFS
    git lfs uninstall
    git lfs install
    git lfs fetch
    git lfs pull

    # Create .gitattributes with all patterns first
    cat > .gitattributes << 'EOF'
* text=auto

# Binary files
*.bin filter=lfs diff=lfs merge=lfs -text
*.o filter=lfs diff=lfs merge=lfs -text
*.so filter=lfs diff=lfs merge=lfs -text
*.so.* filter=lfs diff=lfs merge=lfs -text
*.a filter=lfs diff=lfs merge=lfs -text
*.dll filter=lfs diff=lfs merge=lfs -text
*.dylib filter=lfs diff=lfs merge=lfs -text
*.pyc filter=lfs diff=lfs merge=lfs -text

# Media files
*.onnx filter=lfs diff=lfs merge=lfs -text
*.svg filter=lfs diff=lfs merge=lfs -text
*.png filter=lfs diff=lfs merge=lfs -text
*.gif filter=lfs diff=lfs merge=lfs -text
*.ttf filter=lfs diff=lfs merge=lfs -text
*.wav filter=lfs diff=lfs merge=lfs -text

# Project specific
selfdrive/car/tests/test_models_segs.txt filter=lfs diff=lfs merge=lfs -text
system/hardware/tici/updater filter=lfs diff=lfs merge=lfs -text
selfdrive/ui/qt/spinner_larch64 filter=lfs diff=lfs merge=lfs -text
selfdrive/ui/qt/text_larch64 filter=lfs diff=lfs merge=lfs -text
selfdrive/ui/ui filter=lfs diff=lfs merge=lfs -text
selfdrive/modeld/models/supercombo_tinygrad.pkl filter=lfs diff=lfs merge=lfs -text
EOF

    # Setup LFS tracking
    git add .gitattributes

    # Track binary files
    git lfs track "*.bin" "*.o" "*.so" "*.so.*" "*.a" "*.dll" "*.dylib" "*.pyc"
    git lfs track "*.png" "*.wav" "*.onnx" "*.svg" "*.gif" "*.ttf"
    git lfs track "selfdrive/ui/ui"

    # Fetch and checkout
    git fetch device "$BRANCH_NAME" --force
    git checkout "$BRANCH_NAME" || { echo "ERROR: Failed to checkout branch '$BRANCH_NAME'"; exit 1; }

    # Cherry pick with theirs strategy
    git cherry-pick --no-commit --strategy=recursive -X theirs "$device_commit" || { echo "ERROR: Cherry-pick failed"; exit 1; }

    # Create single commit with all changes
    git lfs track "selfdrive/modeld/models/supercombo_tinygrad.pkl"
    git add -f .
    git commit -m "Prebuilt $(date '+%Y-%m-%d')" || { echo "ERROR: Commit failed"; exit 1; }

    # Push single commit
    git push --force origin "$BRANCH_NAME" || { echo "ERROR: Force push to origin failed"; exit 1; }
}

# Main execution
echo "Starting automated sync process..."

# Always skip recompilation for ... now will change later
COMMIT_HASH=$(skip_compile_device) || exit 1

# Set BRANCH_NAME based on the device's current branch
BRANCH_NAME=$(get_device_branch)
if [[ -z "$BRANCH_NAME" ]]; then
    echo "ERROR: Failed to retrieve the device's current branch."
    exit 1
fi

workspace_operations "$COMMIT_HASH"
echo "Sync process completed."
