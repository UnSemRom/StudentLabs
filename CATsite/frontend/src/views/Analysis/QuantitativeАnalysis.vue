
<template>
  <div class="wrapper-content wrapper-content--fixed">
    <section>
      <div class="container">
        <div class="table-list-js">
          <h1 class="title">Вес слов</h1>
          <div class="table-temp" v-if="!params.data">
            <img src="@/images/tableTemp.svg" />
          </div>
          <div v-else class="table">
            <vue-table-dynamic :params="params"></vue-table-dynamic>
            <div class="button-center">
            <button class="raise" @click="downloadJson()">Скачать аналитику</button>
            </div>
          </div>
        </div>

        <div class="download-list">
          <div class="downloaded-files">
            <div class="input-files">
              <p class="title">Выберите результат по документу</p>
              <input class="downl-file" type="file" id="files" ref="files" multiple v-on:change="handleFilesUpload()" />
            </div>

            <div class="file-list">
              <div v-for="(file, key) in files" v-bind:key="file.id" class="files">
                <div @click="activeBtn = activeBtn === key ? null : key">
                  <div :class="activeBtn === key ? 'files active' : 'files NOactive pulse'">
                    <a>{{ key + 1 + ") " + file.name }}</a>
                    <span class="remove-file" @click.stop v-on:click="removeFile(key)">✘</span>
                  </div>
                </div>
              </div>
            </div>
          </div>

          <div class="buttons-list">
            <button class="pulse" v-on:click="addFiles()">+</button>
            <button class="pulse" v-on:click="submitFile()">Проанализировать</button>
          </div>
        </div>
      </div>
    </section>
  </div>
</template>


<script>
import VueTableDynamic from "vue-table-dynamic";
import download from "downloadjs";
import { mapGetters } from "vuex";
import analysis from "@/utils/analysis";

export default {
  name: "quantitativeAnalysis",

  components: {
    VueTableDynamic
  },

  data() {
    return {
      activeBtn: null,
      files: [],

      params: {
        data: null,
        header: "row",
        stripe: true,
        enableSearch: true,
        sort: [0, 1],
        pagination: true,
        pageSize: 25,
        pageSizes: [5, 15, 25, 55]
      }
    };
  },

  methods: {
    downloadJson() {
      download(
        JSON.stringify(this.params.data.slice(1)),
        "apidata.json",
        "text/plain"
      );
    },

    addFiles() {
      this.$refs.files.click();
    },

    async submitFile() {
      if (this.activeBtn != null) {
        this.params.data = await analysis.quantitativeAnalysis(
          this.files[this.activeBtn]
        );
      } else {
        console.log("Нету выбранных файлов");
      }
    },

    handleFilesUpload() {
      let uploadedFiles = this.$refs.files.files;

      for (var i = 0; i < uploadedFiles.length; i++) {
        this.$store.dispatch("file/setFILE", uploadedFiles[i]);
      }
    },

    removeFile(key) {
      this.files.splice(key, 1);
    }
  },

  computed: {
    ...mapGetters({
      getAllFiles: "file/getAllFiles"
    })
  },

  created() {
    this.files = this.getAllFiles.files;
  }
};
</script>

<style lang="scss" scoped>
@import "@/assets/utils/colors";

.table-list-js{
  width: 50%;
}

.table-temp{
  display: flex;
  justify-content: center;
  height: 50%;
}

.container {
  display: flex;
  justify-content: space-around;
  margin-bottom: 50px;
}

.downloaded-files {
  display: block;
}
.download-list {
  display: flex;
  flex-direction: column;
}

.buttons-list {
  display: flex;
}

input[type="file"] {
  display: none;
}

.files {
  height: 35px;
  line-height: 35px;
  border-radius: 20px;
  background: $second-primary-color;
  margin-bottom: 20px;
  &.active {
    background: $primary-color;
  }
}

a {
  white-space: nowrap;
  overflow: hidden;
  padding-left: 5px;
  color: $text-alternative-color;
}

span.remove-file {
  color: $delete-cross-color;
  cursor: pointer;
  float: right;
  padding-right: 5px;
}

.title {
  text-align: center;
}

.button-center{
  display: flex;
  justify-content: center
}

.table{
  width: 50%;
  margin: auto;
}
</style>
