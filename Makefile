.PHONY: help build test debug clean

help: ## 도움말 표시
# http://marmelab.com/blog/2016/02/29/auto-documented-makefile.html
	@grep -E '^[a-zA-Z0-9_%/-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

build: ## 실행 파일 빌드
	$(MAKE) -C src

test: ## rbtree 구현 테스트
	$(MAKE) -C test test

debug: ## vscode 디버그용
	$(MAKE) -C src clean
	$(MAKE) -C test clean
	$(MAKE) -C src
	$(MAKE) -C test debug

clean: ## 빌드 환경 정리
	$(MAKE) -C src clean
	$(MAKE) -C test clean