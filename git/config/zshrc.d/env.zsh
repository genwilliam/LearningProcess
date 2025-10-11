# 环境变量（PATH、LANG、NVM_DIR 等）
export PATH="/opt/homebrew/bin:$PATH"
export LANG=en_US.UTF-8



# the fuck conf
eval $(thefuck --alias)

export PATH="$HOME/.jenv/bin:$PATH"
eval "$(jenv init -)"



# nvm/deno/docker 等懒加载函数
# Lazy-load NVM when node/npm/npx/nvm command is first used
lazy_load_nvm() {
  unset -f nvm node npm npx
  export NVM_DIR="$HOME/.nvm"
  if [ -s "$NVM_DIR/nvm.sh" ]; then
    # shellcheck source=/dev/null
    . "$NVM_DIR/nvm.sh"
  fi
  if [ -s "$NVM_DIR/bash_completion" ]; then
    # shellcheck source=/dev/null
    . "$NVM_DIR/bash_completion"
  fi
}

nvm() { lazy_load_nvm; nvm "$@"; }
node() { lazy_load_nvm; node "$@"; }
npm() { lazy_load_nvm; npm "$@"; }
npx() { lazy_load_nvm; npx "$@"; }


