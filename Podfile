# プラットフォームの指定
platform :ios, "7.0"

# Xcodeプロジェクトまたはワークスペースの指定
xcodeproj "XcodeCI"
workspace "XcodeCI"

# Podパッケージをリンクさせるターゲット
link_with "XodeCI", "XcodeCI iPad"
# 使用するパッケージとバージョンの宣言
pod "AFNetworking", "~> 2.0.0"

# インストール前に行われるアクション
pre_install do |installer_representation|
  system "gem update --system"
  system "gem update cocoapods"
  p "install started"
end

# ターゲット別の使用パッケージの宣言
target "XcodeCITests", :exclusive => true do
  pod "Kiwi/XCTest"
end

# インストール後に行われるアクション
post_install do |installer_representation|
  p "install finished!"
end
