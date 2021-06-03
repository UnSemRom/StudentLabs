let analysis = {
    async quantitativeAnalysis(file) {
        let params = [
            ["Слово", "Количество"]
        ];
        let files = new FormData();

        files.append("files[]", file);

        axios
            .post("http://127.0.0.1:5000/comparison_frequency_analysis", files)
            .then(res => {

                let dataForTable = Object.entries(res.data.Text0);

                for (let i = 0; i < dataForTable.length; i++) {
                    params.push(dataForTable[i]);
                }
            })
            .catch(function () {
                console.log("Ошибка при анализе")
            })
        return params
    },

    async weightWords(file) {
        let params = [
            ["Слово", "Количество"]
        ];
        let files = new FormData();
        
        files.append("files[]", file);

        axios
            .post("http://127.0.0.1:5000/semantic_analysis", files)
            .then(res => {
                let dataForTable = Object.entries(res.data.data);
                let dataForColumns = Object.entries(res.data.columns);

                for (let i = 0; i < dataForColumns.length; i++) {
                    let temArr = [];
                    temArr.push(dataForColumns[i][1]);
                    temArr.push(dataForTable[0][1][i]);
                    params.push(temArr);
                }
            })
            .catch(function () {
                console.log("Ошибка при анализе");
            });
        return params
    },

    async similarityTexts(allFiles, activeBtns) {
        let params = [];
        let files = new FormData();

        for (var i = 0; i < activeBtns.length; i++) {
            let file = allFiles[activeBtns[i]];
            files.append("files[]", file);
        }

        axios
            .post("http://127.0.0.1:5000/get_tf_idf_query_similarity", files)
            .then(res => {

                let dataForTable = res.data.data;
                let dataForColumns = res.data.columns;
                let dataForIndex = res.data.index;

                dataForColumns.unshift("");
                params.push(dataForColumns);

                for (var i = 0; i < dataForIndex.length; i++) {
                    dataForTable[i].unshift(dataForIndex[i]);
                    params.push(dataForTable[i]);
                }
            })
            .catch(function () {
                console.log("Вывести ошибку");
            });
        return params
    },

    async wordCloud(file) {
        let paramsData = [];
        let files = new FormData();

        files.append("files[]", file);

        axios
            .post("http://127.0.0.1:5000/comparison_frequency_analysis", files)
            .then(res => {
                let dataForTable = Object.entries(res.data.Text0);

                for (let i = 0; i < dataForTable.length; i++) {
                    let dataTemp = {}
                    dataTemp["name"] = dataForTable[i][0]
                    dataTemp["value"] =dataForTable[i][1]
                     
                    paramsData.push(dataTemp);
            }
        })
            .catch(function () {
                console.log("Вывести ошибку");
            });
        return paramsData
    }
}

export default analysis