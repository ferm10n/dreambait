<template>
  <v-app dark>
    <v-content id="test">
      <v-container
        fluid
        fill-height
      >
        <v-layout
          align-center
          justify-center
        >
          <v-flex
            xs12
            sm8
            md4
          >
            <v-card
              class="elevation-12"
              light
            >
              <v-toolbar
                color="primary"
                dark
              >
                <v-toolbar-title>
                  WiFi Settings
                </v-toolbar-title>
              </v-toolbar>
              <v-form>
                <v-card-text>
                  <v-text-field name="ssid" label="WiFi Network" type="text" />
                  <v-text-field name="password" label="Password" type="text" />
                </v-card-text>
                <v-toolbar
                  color="primary"
                  dark
                >
                  <v-toolbar-title>
                    Device Settings
                  </v-toolbar-title>
                </v-toolbar>
                <v-card-text>
                  <p>What should activate the lights?</p>
                  <v-radio-group v-model="activateMethod" row>
                    <v-radio
                      label="Detecting device presence"
                      value="detect"
                    />
                    <v-radio
                      label="Manual"
                      value="manual"
                    />
                  </v-radio-group>
                </v-card-text>
                <v-card-text v-if="activateMethod === 'detect'">
                  <v-layout wrap>
                    <v-flex xs12 sm8 pr-2>
                      <v-text-field name="blueip" label="IP for Blue" type="text" />
                    </v-flex>
                    <v-flex xs12 sm4>
                      <v-btn block color="blue" dark>THIS DEVICE</v-btn>
                    </v-flex>
                  </v-layout>
                  <v-layout wrap>
                    <v-flex xs12 sm8 pr-2>
                      <v-text-field name="redip" label="IP for Red" type="text" />
                    </v-flex>
                    <v-flex xs12 sm4>
                      <v-btn block color="red" dark>THIS DEVICE</v-btn>
                    </v-flex>
                  </v-layout>
                </v-card-text>
                <v-card-text v-if="activateMethod === 'manual'">
                  <hr>
                  <v-layout>
                    <v-flex
                      xs12
                      sm6
                    >
                      <v-checkbox
                        v-model="activateBlue"
                        label="Enable Blue"
                        color="blue"
                      />
                    </v-flex>
                    <v-flex
                      xs12
                      sm6
                    >
                      <v-checkbox
                        v-model="activateRed"
                        label="Enable Red"
                        color="red"
                      />
                    </v-flex>
                  </v-layout>
                </v-card-text>
                <v-card-text>
                  <v-slider
                    v-model="speed"
                    label="Speed"
                  />
                </v-card-text>
              </v-form>
            </v-card>
          </v-flex>
        </v-layout>
      </v-container>
    </v-content>
  </v-app>
</template>

<script>
export default {
  el: '#app',
  name: 'RootApp',
  data () {
    return {
      activateMethod: 'detect',
      activateRed: true,
      activateBlue: true
    };
  }
};
</script>

<style lang="stylus" scoped>
#test
  background-image url(./background.svg)
  background-size contain
  background-position center
</style>
