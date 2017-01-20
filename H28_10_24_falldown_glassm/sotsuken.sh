#!/bin/sh


echo "||=================================================||"
echo "||Welcome to Kurumada.Lab's movie analysis program!||"
echo "||=================================================||"

getopts y opts
outdir="out/two/txt/and/"

#全自動
case $opts in
	y)
		echo "フルオートモードで動作します。"
		echo "動画名を入力してください。"
		read moviename
		echo "動画の再生位置を入力してください(秒数)。"
		read start
		echo "動画の停止位置を入力してください(秒数)。"
		read stop
		echo "ベースとするフレームを入力してください。(整数)"
		read num
		echo "重なり結果を出力するファイル名を入力してください。"
		read resultname
		echo "相関結果を出力するファイル名を入力してください。"
		read solname
		echo "フーリエ結果を出力するファイル名を入力してください。"
		read fouriename
	
		#0		
		echo "エンコード中・・・"
		rm penguine.mp4
		ffmpeg -i $moviename -ss $start -t `expr $stop - $start` penguine.mp4 
		echo "エンコードが完了しました。"
		echo "penguine.mp4を確認してください。"
		#1
		echo "フレーム抽出中・・・"
		rm -rf out/
		mkdir out
		mkdir out/tri
		mkdir out/two
		mkdir out/two/txt
		mkdir out/two/txt/and
		python3 getimage.py
		echo "フレーム抽出が完了しました。"
		echo "outディレクトリを確認してください。"
		#2
		echo "テキスト出力中・・・"
		./E_getbw
		echo "フレーム抽出が完了しました。"
		echo "out/two/txtディレクトリを確認してください。"
		#3
		echo "計算出力中・・・"
		python3 andbw.py $num $resultname
		tmp1="${outdir}${resultname}"
		tmp2="${outdir}sort_${resultname}"
		cat $tmp1 | sort -R > $tmp2
		echo "重なり計算が完了しました。"
		echo "out/two/txt/andディレクトリを確認してください。"
		#4
		echo "計算出力中・・・"
		tmp2="sort_${resultname}"
		tmp3="sort_${solname}"
		tmp4="sort_${fouriename}"
		./E_solvecorr $resultname $solname $fouriename
		./E_solvecorr $tmp2 $tmp3 $tmp4
		echo "相関関数の計算が完了しました。"
		echo "out/two/txt/andディレクトリを確認してください。"
		exit
		;;
esac

echo "【0】動画エンコード(avi -> mp4)を行います。"
echo "エンコードしますか？(y/n)"
read s0
if [ $s0 = "y" ]
then
	echo "動画名を入力してください。"
	read moviename
	echo "動画の再生位置を入力してください(秒数)。"
	read start
	echo "動画の停止位置を入力してください(秒数)。"
	read stop
	echo "エンコード中・・・"
	rm penguine.mp4
	ffmpeg -i $moviename -ss $start -t `expr $stop - $start` penguine.mp4 
	echo "エンコードが完了しました。"
	echo "penguine.mp4を確認してください。"
elif [ $s0 = "n" ]
then
	echo "ステップ0をスキップします"
else
	echo "不正なパラメータを受け付けました。プログラムを終了します。"
	exit
fi

echo "【1】フレーム抽出を行います。"
echo "フレーム抽出を行いますか？(y/n)"
read s1
if [ $s1 = "y" ]
then
	echo "フレーム抽出中・・・"
	rm -rf out/
	mkdir out
	mkdir out/tri
	mkdir out/two
	mkdir out/two/txt
	mkdir out/two/txt/and
	python3 getimage.py
	echo "フレーム抽出が完了しました。"
	echo "outディレクトリを確認してください。"
elif [ $s1 = "n" ]
then
	echo "ステップ1をスキップします"
else
	echo "不正なパラメータを受け付けました。プログラムを終了します。"
	exit
fi

echo "【2】白(1)、黒(0)としてピクセルデータのテキスト出力をします。"
echo "テキスト化を行いますか？(y/n)"
read s2
if [ $s2 = "y" ]
then
	echo "テキスト出力中・・・"
	./E_getbw
	echo "フレーム抽出が完了しました。"
	echo "out/two/txtディレクトリを確認してください。"
elif [ $s2 = "n" ]
then
	echo "ステップ2をスキップします"
else
	echo "不正なパラメータを受け付けました。プログラムを終了します。"
	exit
fi

echo "【3】ベースフレームとの比較を行います。"
echo "比較を行いますか？(y/n)"
read s3
if [ $s3 = "y" ]
then
	echo "ベースとするフレームを入力してください。(整数)"
	read num
	echo "結果を出力するファイル名を入力してください。"
	read resultname
	echo "計算出力中・・・"
	python3 andbw.py $num $resultname
	tmp1="${outdir}${resultname}"
	tmp2="${outdir}sort_${resultname}"
	cat $tmp1 | sort -R > $tmp2
	echo "重なり計算が完了しました。"
	echo "out/two/txt/andディレクトリを確認してください。"
elif [ $s3 = "n" ]
then
	echo "ステップ3をスキップします"
else
	echo "不正なパラメータを受け付けました。プログラムを終了します。"
	exit
fi

echo "【4】相関関数・フーリエ変換を求めます。"
echo "相関関数・フーリエ変換を求めますか？(y/n)"
read s4
if [ $s4 = "y" ]
then
	echo "入力する結果ファイル名を入力してください。"
	read resultname
	echo "相関関数結果を出力するファイル名を入力してください。"
	read solname
	echo "フーリエ結果を出力するファイル名を入力してください。"
	read fouriename
	echo "計算出力中・・・"
	tmp2="sort_${resultname}"
	tmp3="sort_${solname}"
	tmp4="sort_${fouriename}"
	./E_solvecorr $resultname $solname $fouriename
	./E_solvecorr $tmp2 $tmp3 $tmp4
	echo "相関関数の計算が完了しました。"
	echo "out/two/txt/andディレクトリを確認してください。"
elif [ $s4 = "n" ]
then
	echo "ステップ4をスキップします"
else
	echo "不正なパラメータを受け付けました。プログラムを終了します。"
	exit
fi
